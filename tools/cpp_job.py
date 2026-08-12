#!/usr/bin/env python3
"""Build and verify a resumable readable-C++ reconstruction job.

The job folder is a local, gitignored research workspace.  ``create`` gathers
the ROM-backed target, relocations, current source/header context, prior match
attempts, optional emulator evidence, and an m2c semantic draft.  A contributor
or agent edits only ``candidate.cpp``.  ``verify`` compiles that candidate with
the canonical mwccarm build and requires linked-byte verification before it
marks the job promotion-ready.

This tool never writes to ``src/``.  A verified candidate can be promoted in a
separate, deliberate change using ``tools/srcpath.py`` and the normal claims,
attempt, and provenance workflow described by AGENTS.md.
"""
from __future__ import annotations

import argparse
import datetime as dt
import hashlib
import json
import pathlib
import re
import shutil
import sys
from typing import Any

TOOLS = pathlib.Path(__file__).resolve().parent
REPO = TOOLS.parent
TRACE = TOOLS / "trace"
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(TRACE))

import bplist  # noqa: E402
import cpp_probe  # noqa: E402
import extern_c_wrap  # noqa: E402
import linkcheck as LC  # noqa: E402
import m2c_draft  # noqa: E402
import match as M  # noqa: E402
import modules as MOD  # noqa: E402
import probe_versions as PV  # noqa: E402
import reloc_audit as RA  # noqa: E402
import relocs as R  # noqa: E402
import srcpath  # noqa: E402
import swarm as S  # noqa: E402


SCHEMA = "sm64ds-cpp-research-job-v1"
VERIFY_SCHEMA = "sm64ds-cpp-verification-v1"


class JobError(RuntimeError):
    pass


def _now() -> str:
    return dt.datetime.now(dt.timezone.utc).isoformat()


def _safe_name(value: str) -> str:
    result = re.sub(r"[^A-Za-z0-9_.-]+", "_", value).strip(".")
    return result or "target"


def _relative(path: pathlib.Path, base: pathlib.Path = REPO) -> str:
    path = pathlib.Path(path).resolve()
    try:
        return path.relative_to(base.resolve()).as_posix()
    except ValueError:
        return str(path)


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def _write_json(path: pathlib.Path, value: Any) -> None:
    path.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n",
                    encoding="utf-8")


def _read_job(path: pathlib.Path) -> tuple[pathlib.Path, dict[str, Any]]:
    path = pathlib.Path(path)
    manifest = path / "job.json" if path.is_dir() else path
    if not manifest.is_file():
        raise JobError(f"job manifest not found: {manifest}")
    data = json.loads(manifest.read_text(encoding="utf-8"))
    if data.get("schema") != SCHEMA:
        raise JobError(f"unsupported job schema in {manifest}")
    return manifest.parent.resolve(), data


def resolve_target(spec: str, extracted: str | None = None) -> dict[str, Any]:
    targets, missing = bplist.from_names([spec], repo=REPO, extracted=extracted)
    if missing or len(targets) != 1:
        raise JobError(
            f"could not resolve {spec!r}; use module:symbol when a name is ambiguous")
    return targets[0]


def _module(target: dict[str, Any]) -> dict[str, Any]:
    wanted = target["module"]
    for module in MOD.modules():
        label = "arm9" if module["name"] == "main" else module["name"]
        if label == wanted:
            return module
    raise JobError(
        f"module {wanted} has no local extracted binary; run tools/unpack.py or set up extracts")


def _target_bytes(target: dict[str, Any]) -> tuple[bytes, dict[str, Any]]:
    module = _module(target)
    size = target.get("size")
    if not isinstance(size, int) or size <= 0:
        raise JobError(f"target {target['name']} has no usable configured size")
    data = MOD.read_bytes(module, target["addr"], size)
    if len(data) != size:
        raise JobError(
            f"target bytes are truncated: expected {size:#x}, found {len(data):#x}")
    return data, module


def _relocations(target: dict[str, Any], module: dict[str, Any]) -> list[dict[str, Any]]:
    if not module["relocs"].is_file():
        return []
    symbols = R.load_all_syms()
    result = []
    end = target["addr"] + target["size"]
    for address, reloc in sorted(R.load_relocs_file(module["relocs"]).items()):
        if target["addr"] <= address < end:
            result.append({
                "offset": address - target["addr"],
                "from": f"0x{address:08x}",
                "kind": reloc[0],
                "to": f"0x{reloc[1]:08x}",
                "to_module": reloc[2],
                "symbol": R.name_for_reloc(reloc, symbols),
            })
    return result


def _matching_rows(path: pathlib.Path, target: dict[str, Any]) -> list[dict[str, Any]]:
    if not path.is_file():
        return []
    result = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        if not line.strip():
            continue
        try:
            row = json.loads(line)
        except json.JSONDecodeError:
            continue
        addr = row.get("addr")
        try:
            addr = int(addr, 0) if isinstance(addr, str) else int(addr)
        except (TypeError, ValueError):
            addr = None
        row_module = row.get("module", "arm9")
        if (row_module == target["module"] and
                (row.get("name") == target["name"] or addr == target["addr"])):
            result.append(row)
    return result


def _prior_work(target: dict[str, Any]) -> dict[str, Any]:
    attempts = _matching_rows(REPO / "config" / "match_attempts.jsonl", target)
    provenance = _matching_rows(REPO / "config" / "match_provenance.jsonl", target)
    near_misses = _matching_rows(REPO / "nearmiss" / "db.jsonl", target)
    near_misses.sort(key=lambda row: row.get("divergences", 1 << 30))
    return {
        "attempts": attempts,
        "provenance": provenance,
        "near_misses": near_misses,
    }


def _semantic_artifacts(job_dir: pathlib.Path, target: dict[str, Any]) -> dict[str, Any]:
    result: dict[str, Any] = {
        "assembly": None,
        "semantic_draft": None,
        "m2c_status": "not-run",
    }
    try:
        label, name, addr, _size, data, window = m2c_draft.resolve_live(
            target["name"], target["module"], target["addr"], target["size"])
        relocs = R.load_relocs_file(m2c_draft.reloc_file_for(label))
        symbols = R.load_all_syms()
        assembly = m2c_draft.build_asm(name, addr, data, relocs, symbols, window)
        asm_path = job_dir / "target.s"
        asm_path.write_text(assembly, encoding="utf-8")
        result["assembly"] = asm_path.name
        try:
            draft = m2c_draft.draft(name, addr, data, relocs, symbols, window)
            draft_path = job_dir / "semantic_draft.c"
            draft_path.write_text(draft, encoding="utf-8")
            result["semantic_draft"] = draft_path.name
            result["m2c_status"] = "generated"
        except (m2c_draft.M2CError, OSError, TimeoutError) as exc:
            result["m2c_status"] = "unavailable"
            result["m2c_error"] = str(exc)
    except (m2c_draft.M2CError, OSError, SystemExit, ValueError) as exc:
        result["m2c_status"] = "assembly-failed"
        result["m2c_error"] = str(exc)
    return result


def _copy_runtime_evidence(job_dir: pathlib.Path,
                           paths: list[str]) -> list[dict[str, Any]]:
    if not paths:
        return []
    destination = job_dir / "runtime"
    destination.mkdir(exist_ok=True)
    result = []
    used = set()
    for raw in paths:
        source = pathlib.Path(raw).resolve()
        if not source.is_file():
            raise JobError(f"runtime evidence not found: {source}")
        try:
            data = json.loads(source.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError) as exc:
            raise JobError(f"invalid runtime evidence {source}: {exc}") from exc
        name = source.name
        stem, suffix = source.stem, source.suffix
        index = 2
        while name in used:
            name = f"{stem}_{index}{suffix}"
            index += 1
        used.add(name)
        copied = destination / name
        shutil.copy2(source, copied)
        result.append({
            "path": copied.relative_to(job_dir).as_posix(),
            "source": str(source),
            "sha256": _sha256(copied.read_bytes()),
            "schema": data.get("schema"),
            "question": data.get("question"),
            "cases": len(data.get("cases", [])),
            "expectations": data.get("expectations", []),
        })
    return result


def _c_to_cpp_seed(text: str, target: dict[str, Any],
                   relocations: list[dict[str, Any]]) -> str:
    """Preserve ROM linkage while turning a one-function C TU into a C++ seed."""
    names = {row["symbol"] for row in relocations if row.get("symbol")}
    wrapped = extern_c_wrap.wrap(text, names)
    text = wrapped if wrapped is not None else text
    symbol = re.escape(target["name"])
    definition = re.compile(
        rf"(?m)^(?![ \t]*extern[ \t]+\"C\")(?P<indent>[ \t]*)"
        rf"(?P<head>[^\n#;/{{}}]*\b{symbol}[ \t]*\()")
    text, count = definition.subn(
        lambda match: f'{match.group("indent")}extern "C" {match.group("head")}',
        text, count=1)
    note = (
        f"// Research seed converted from C for {target['module']}:{target['name']}.\n"
        "// ROM callees and the target retain C linkage; introduce readable C++ names deliberately.\n"
        "// This workspace file is not promotion-ready until cpp_job.py verify says VERIFIED.\n"
    )
    if count == 0:
        note += "// WARNING: target definition was not found for automatic C-linkage wrapping.\n"
    return "//cpp\n" + note + text


def _candidate_seed(job_dir: pathlib.Path, target: dict[str, Any],
                    source: pathlib.Path | None,
                    prior: dict[str, Any], relocations: list[dict[str, Any]],
                    reset: bool) -> dict[str, Any]:
    candidate = job_dir / "candidate.cpp"
    if source is not None:
        text = source.read_text(encoding="utf-8", errors="replace")
        snapshot = job_dir / f"source_snapshot{source.suffix}"
        snapshot.write_text(text, encoding="utf-8")
    if candidate.exists() and not reset:
        return {"path": candidate.name, "seed": "preserved"}

    if source is not None:
        if source.suffix == ".cpp" and text.startswith("//cpp"):
            seed = text
            kind = "existing-cpp"
        else:
            seed = _c_to_cpp_seed(text, target, relocations)
            kind = "existing-c-to-cpp"
    else:
        best = next((row for row in prior["near_misses"] if row.get("c_source")), None)
        if best:
            text = best["c_source"]
            seed = (text if text.startswith("//cpp")
                    else _c_to_cpp_seed(text, target, relocations))
            kind = "near-miss"
            (job_dir / "best_nearmiss_source.txt").write_text(text, encoding="utf-8")
        else:
            seed = (
                "//cpp\n"
                f"// TODO: reconstruct {target['module']}:{target['name']} from this job's evidence.\n"
                "// Do not move this file into src/ until verification.json says VERIFIED.\n"
            )
            kind = "empty-template"
    candidate.write_text(seed, encoding="utf-8")
    return {"path": candidate.name, "seed": kind}


def _task_markdown(job: dict[str, Any]) -> str:
    target = job["target"]
    source = job["source"]
    layout = job["cpp_context"]
    runtime = job["runtime_evidence"]
    command_path = pathlib.PurePosixPath(job["job_path"])
    lines = [
        f"# C++ reconstruction job: `{target['name']}`",
        "",
        "## Objective",
        "",
        f"Produce readable C++ for `{target['module']}:{target['name']}` at "
        f"`{target['address']}` without changing canonical `src/` until the "
        "candidate reproduces and links to the ROM exactly.",
        "",
        "## Evidence already assembled",
        "",
        f"- Target: `{target['size']}` bytes, SHA-256 `{target['sha256']}`.",
        f"- Relocations: {len(job['relocations'])} configured slot(s) in `relocations.json`.",
        f"- Existing source: `{source.get('existing') or 'none'}`.",
        f"- Proposed canonical path: `{source['proposed_cpp_path']}`.",
        f"- C++ class/header: `{layout.get('class') or 'unknown'}` / "
        f"`{layout.get('header') or 'none'}`.",
        f"- Semantic assembly: `{job['static'].get('assembly') or 'unavailable'}`.",
        f"- m2c comprehension draft: `{job['static'].get('semantic_draft') or 'unavailable'}` "
        "(never a matching candidate by itself).",
        f"- Runtime captures: {len(runtime)}.",
        f"- Prior attempts: {len(job['prior_work']['attempts'])}; "
        f"near-misses: {len(job['prior_work']['near_misses'])}.",
        "",
        "## Work loop",
        "",
        "1. Read `target.s`, `relocations.json`, the source snapshot, reconstructed header, "
        "and every file under `runtime/`.",
        "2. Edit only `candidate.cpp`. Treat runtime observations as constraints, not proof "
        "of unobserved paths, names, signedness, or byte identity.",
        "3. Run the verifier after each coherent candidate:",
        "",
        "```powershell",
        f"python tools\\cpp_job.py verify {str(command_path).replace('/', chr(92))}",
        "```",
        "",
        "4. Continue until `verification.json` reports `verdict: VERIFIED`, "
        "`compiler_version: 2004/b56`, `byte_match: true`, and `blind: 0`.",
        "5. Only then claim/promote the emitted symbol through `tools/srcpath.py`, log the "
        "attempt and provenance, and run the repository's pre-push gates. Do not bundle this "
        "tooling/job artifact into a source-match PR.",
        "",
        "## Hard proof boundary",
        "",
        "A plausible decompilation, an m2c draft, a runtime hit, or a loose byte match is not "
        "completion. Promotion requires the verifier's linked-byte `VERIFIED` result.",
        "",
    ]
    return "\n".join(lines)


def create_job(spec: str, out: str | None = None, extracted: str | None = None,
               runtime_evidence: list[str] | None = None,
               reset_candidate: bool = False) -> pathlib.Path:
    target = resolve_target(spec, extracted)
    target_data, module = _target_bytes(target)
    default = REPO / "progress" / "cpp-jobs" / target["module"] / _safe_name(target["name"])
    job_dir = pathlib.Path(out).resolve() if out else default.resolve()
    job_dir.mkdir(parents=True, exist_ok=True)
    existing_job: dict[str, Any] = {}
    existing_manifest = job_dir / "job.json"
    if existing_manifest.is_file():
        try:
            loaded = json.loads(existing_manifest.read_text(encoding="utf-8"))
            if loaded.get("schema") == SCHEMA:
                existing_job = loaded
        except (OSError, json.JSONDecodeError):
            pass

    source = srcpath.path_for(target["name"])
    prior = _prior_work(target)
    layout = cpp_probe.discover_layout(target["name"], repo=REPO)
    relocations = _relocations(target, module)
    (job_dir / "target.bin").write_bytes(target_data)
    _write_json(job_dir / "relocations.json", relocations)
    _write_json(job_dir / "prior_work.json", prior)
    static = _semantic_artifacts(job_dir, target)
    copied_runtime = _copy_runtime_evidence(job_dir, runtime_evidence or [])
    runtime = []
    seen_runtime = set()
    for item in [*existing_job.get("runtime_evidence", []), *copied_runtime]:
        key = item.get("sha256") or item.get("path")
        if key not in seen_runtime:
            seen_runtime.add(key)
            runtime.append(item)
    candidate = _candidate_seed(
        job_dir, target, source, prior, relocations, reset_candidate)

    proposed = srcpath.new_path_for(target["name"], ".cpp")
    job = {
        "schema": SCHEMA,
        "created_at": existing_job.get("created_at", _now()),
        "updated_at": _now(),
        "job_path": _relative(job_dir),
        "target": {
            "requested": spec,
            "name": target["name"],
            "module": target["module"],
            "address": f"0x{target['addr']:08x}",
            "size": target["size"],
            "instruction_set": target.get("instruction_set", "arm"),
            "canary": target["canary"],
            "canary_source": target.get("canary_source"),
            "sha256": _sha256(target_data),
            "binary": "target.bin",
        },
        "module": {
            "binary": _relative(module["bin"]),
            "base": f"0x{module['base']:08x}",
            "symbols": _relative(module["syms"]),
            "relocs": _relative(module["relocs"]),
        },
        "source": {
            "existing": _relative(source) if source else None,
            "proposed_cpp_path": _relative(proposed),
            "candidate": candidate,
        },
        "cpp_context": layout,
        "relocations": relocations,
        "prior_work": {
            "attempts": prior["attempts"],
            "provenance": prior["provenance"],
            "near_misses": prior["near_misses"],
        },
        "static": static,
        "runtime_evidence": runtime,
        "verification": existing_job.get("verification"),
    }
    verification = job.get("verification") or {}
    candidate_path = job_dir / candidate["path"]
    if (reset_candidate or not candidate_path.is_file() or
            verification.get("candidate_sha256") != _sha256(candidate_path.read_bytes()) or
            verification.get("target", {}).get("sha256") != job["target"]["sha256"]):
        job["verification"] = None
    _write_json(job_dir / "job.json", job)
    (job_dir / "TASK.md").write_text(_task_markdown(job), encoding="utf-8")
    return job_dir


def _candidate_functions(obj: bytes, requested: str | None = None) -> list[str]:
    names = list(PV.funcs_in(obj))
    if requested and requested in names:
        names.remove(requested)
        names.insert(0, requested)
    return names


def verify_job(path: str, candidate: str | None = None,
               candidate_symbol: str | None = None) -> dict[str, Any]:
    job_dir, job = _read_job(pathlib.Path(path))
    target = job["target"]
    candidate_path = (pathlib.Path(candidate).resolve() if candidate else
                      (job_dir / job["source"]["candidate"]["path"]).resolve())
    if not candidate_path.is_file():
        raise JobError(f"candidate not found: {candidate_path}")
    target_data = (job_dir / target["binary"]).read_bytes()
    if _sha256(target_data) != target["sha256"]:
        raise JobError("target.bin hash differs from job.json; recreate the job")

    source_text = candidate_path.read_text(encoding="utf-8", errors="replace")
    flags = S.CPP_FLAGS if source_text.startswith("//cpp") else M.DEFAULT_FLAGS
    result: dict[str, Any] = {
        "schema": VERIFY_SCHEMA,
        "created_at": _now(),
        "candidate": str(candidate_path),
        "candidate_sha256": _sha256(candidate_path.read_bytes()),
        "compiler_version": M.CANONICAL,
        "target": {
            "name": target["name"],
            "module": target["module"],
            "address": target["address"],
            "size": target["size"],
            "sha256": target["sha256"],
        },
        "compiled": False,
        "byte_match": False,
        "promotion_ready": False,
        "verdict": "COMPILE-FAILED",
    }
    obj = M.compile_c(candidate_path, M.CANONICAL, flags)
    if obj is None:
        _write_json(job_dir / "verification.json", result)
        job["verification"] = result
        _write_json(job_dir / "job.json", job)
        return result
    result["compiled"] = True

    requested = candidate_symbol or target["name"]
    candidates = _candidate_functions(obj, requested)
    if candidate_symbol and candidate_symbol not in candidates:
        result.update({"verdict": "NO-CANDIDATE-SYMBOL",
                       "reason": f"{candidate_symbol!r} is not emitted",
                       "emitted_symbols": candidates})
    else:
        exact = []
        closest = None
        inspect = [candidate_symbol] if candidate_symbol else candidates
        for symbol in inspect:
            code, relocs = M.extract_func(obj, symbol)
            if code is None:
                continue
            ok, differences = M.compare(target_data, code, relocs, verbose=False)
            row = {"symbol": symbol, "size": len(code), "word_differences": differences}
            if ok:
                exact.append((symbol, obj, row))
            if closest is None or differences < closest["word_differences"]:
                closest = row

        result["emitted_symbols"] = candidates
        result["exact_symbols"] = [row for _symbol, _obj, row in exact]
        result["closest"] = closest
        if not exact:
            result["verdict"] = "NO-BYTE-MATCH"
        else:
            name_index = RA.build_name_index()
            checks = []
            for symbol, candidate_obj, row in exact:
                check = LC.linkcheck(
                    target["name"], int(target["address"], 0), target["size"],
                    target["module"], name_index, obj=candidate_obj, sym=symbol)
                checks.append({"symbol": symbol, **check})
            result["byte_match"] = True
            result["linkchecks"] = checks
            verified = [check for check in checks
                        if check["verdict"] == "VERIFIED" and check.get("blind", 0) == 0]
            if len(verified) == 1:
                result.update({
                    "verdict": "VERIFIED",
                    "emitted_symbol": verified[0]["symbol"],
                    "blind": 0,
                    "promotion_ready": True,
                })
            elif len(verified) > 1:
                result.update({
                    "verdict": "AMBIGUOUS-VERIFIED-SYMBOL",
                    "reason": "pass --candidate-symbol to select the intended emitted function",
                    "blind": 0,
                })
            else:
                result["verdict"] = checks[0]["verdict"] if len(checks) == 1 else "LINKCHECK-FAILED"
                result["blind"] = sum(check.get("blind", 0) for check in checks)

    _write_json(job_dir / "verification.json", result)
    job["verification"] = result
    _write_json(job_dir / "job.json", job)
    return result


def print_status(job_dir: pathlib.Path, job: dict[str, Any]) -> None:
    target = job["target"]
    verification = job.get("verification") or {}
    print(f"job: {_relative(job_dir)}")
    print(f"target: {target['module']}:{target['name']} {target['address']} size={target['size']:#x}")
    print(f"candidate: {job['source']['candidate']['path']} "
          f"(seed={job['source']['candidate']['seed']})")
    print(f"class/header: {job['cpp_context'].get('class') or '-'} / "
          f"{job['cpp_context'].get('header') or '-'}")
    print(f"runtime evidence: {len(job.get('runtime_evidence', []))}")
    print(f"verification: {verification.get('verdict', 'NOT-RUN')}")
    if verification.get("closest"):
        closest = verification["closest"]
        print(f"closest: {closest['symbol']} ({closest['word_differences']} word(s) differ)")
    if verification.get("promotion_ready"):
        print(f"promotion-ready: yes ({verification['emitted_symbol']}, linked bytes VERIFIED)")
    else:
        print("promotion-ready: no")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)

    create = sub.add_parser("create", help="assemble or refresh a research job")
    create.add_argument("target", help="symbol or module:symbol")
    create.add_argument("--out", help="job directory (default progress/cpp-jobs/...)")
    create.add_argument("--extracted", help="ROM extraction directory")
    create.add_argument("--runtime-evidence", action="append", default=[],
                        help="cpp_probe/scenario JSON to copy into the job (repeatable)")
    create.add_argument("--reset-candidate", action="store_true",
                        help="replace candidate.cpp from current source/prior work")

    verify = sub.add_parser("verify", help="compile and link-verify a job candidate")
    verify.add_argument("job", help="job directory or job.json")
    verify.add_argument("--candidate", help="candidate source override")
    verify.add_argument("--candidate-symbol",
                        help="emitted symbol to verify when the TU has multiple matches")

    status = sub.add_parser("status", help="summarize a job and its last verification")
    status.add_argument("job", help="job directory or job.json")

    args = parser.parse_args(argv)
    try:
        if args.command == "create":
            job_dir = create_job(
                args.target, args.out, args.extracted,
                args.runtime_evidence, args.reset_candidate)
            _job_dir, job = _read_job(job_dir)
            print_status(job_dir, job)
            print(f"task: {job_dir / 'TASK.md'}")
            return 0
        if args.command == "verify":
            result = verify_job(args.job, args.candidate, args.candidate_symbol)
            print(json.dumps(result, indent=2, sort_keys=True))
            return 0 if result.get("promotion_ready") else 1
        job_dir, job = _read_job(pathlib.Path(args.job))
        print_status(job_dir, job)
        return 0
    except (JobError, OSError, ValueError, json.JSONDecodeError) as exc:
        print(f"cpp job error: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
