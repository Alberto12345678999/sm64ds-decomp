"""Tests for the resumable readable-C++ research job tool."""
import json
import pathlib
import sys


TOOLS = pathlib.Path(__file__).resolve().parent
sys.path.insert(0, str(TOOLS))

import cpp_job as J  # noqa: E402


def test_safe_name_preserves_mangled_symbol_prefix():
    assert J._safe_name("_ZN5Fader13AdvanceInterpEv") == "_ZN5Fader13AdvanceInterpEv"


def _manifest(job_dir, target=b"\x01\x02\x03\x04"):
    (job_dir / "target.bin").write_bytes(target)
    (job_dir / "candidate.cpp").write_text(
        "//cpp\nvoid Candidate() {}\n", encoding="utf-8")
    data = {
        "schema": J.SCHEMA,
        "job_path": str(job_dir),
        "target": {
            "name": "Original",
            "module": "arm9",
            "address": "0x02004000",
            "size": len(target),
            "sha256": J._sha256(target),
            "binary": "target.bin",
        },
        "source": {
            "candidate": {"path": "candidate.cpp", "seed": "test"},
        },
        "cpp_context": {},
        "runtime_evidence": [],
        "verification": None,
    }
    J._write_json(job_dir / "job.json", data)
    return data


def test_matching_rows_joins_by_module_and_address(tmp_path):
    ledger = tmp_path / "ledger.jsonl"
    ledger.write_text(
        json.dumps({"name": "Other", "module": "ov002",
                    "addr": "0x02005000", "value": 1}) + "\n" +
        json.dumps({"name": "Wanted", "module": "ov006",
                    "addr": 0x02005000, "value": 2}) + "\n",
        encoding="utf-8")
    target = {"name": "Wanted", "module": "ov002", "addr": 0x02005000}

    rows = J._matching_rows(ledger, target)

    assert [row["value"] for row in rows] == [1]


def test_candidate_seed_preserves_existing_work_without_reset(tmp_path):
    candidate = tmp_path / "candidate.cpp"
    candidate.write_text("//cpp\n// human work\n", encoding="utf-8")

    result = J._candidate_seed(
        tmp_path, {"name": "Target", "module": "arm9"}, None,
        {"near_misses": []}, [], reset=False)

    assert result == {"path": "candidate.cpp", "seed": "preserved"}
    assert "human work" in candidate.read_text(encoding="utf-8")


def test_c_to_cpp_seed_preserves_target_and_rom_callee_linkage():
    source = (
        "extern int Callee(int value);\n"
        "int func_02004000(int value)\n"
        "{\n"
        "    return Callee(value);\n"
        "}\n"
    )

    seed = J._c_to_cpp_seed(
        source, {"module": "arm9", "name": "func_02004000"},
        [{"symbol": "Callee"}])

    assert seed.startswith("//cpp\n")
    assert 'extern "C" {\nextern int Callee(int value);\n}' in seed
    assert 'extern "C" int func_02004000(int value)' in seed


def test_create_job_assembles_context_without_overwriting_candidate(tmp_path, monkeypatch):
    source = tmp_path / "source.cpp"
    source.write_text("//cpp\nvoid Original() {}\n", encoding="utf-8")
    symbols = tmp_path / "symbols.txt"
    relocs = tmp_path / "relocs.txt"
    binary = tmp_path / "module.bin"
    for path in (symbols, relocs, binary):
        path.write_bytes(b"")
    target = {
        "name": "Original", "module": "arm9", "addr": 0x02004000,
        "size": 4, "canary": "01020304", "canary_source": "test",
        "instruction_set": "arm",
    }
    module = {"name": "main", "base": 0x02004000, "bin": binary,
              "syms": symbols, "relocs": relocs}
    monkeypatch.setattr(J, "resolve_target", lambda *_args, **_kwargs: target)
    monkeypatch.setattr(J, "_target_bytes", lambda _target: (b"\x01\x02\x03\x04", module))
    monkeypatch.setattr(J, "_relocations", lambda *_args: [])
    monkeypatch.setattr(J, "_prior_work", lambda _target: {
        "attempts": [], "provenance": [], "near_misses": []})
    monkeypatch.setattr(J, "_semantic_artifacts", lambda *_args: {
        "assembly": "target.s", "semantic_draft": None,
        "m2c_status": "unavailable"})
    monkeypatch.setattr(J.cpp_probe, "discover_layout", lambda *_args, **_kwargs: {
        "class": "Original", "header": "include/Original.h"})
    monkeypatch.setattr(J.srcpath, "path_for", lambda _symbol: source)
    monkeypatch.setattr(J.srcpath, "new_path_for",
                        lambda _symbol, _ext: J.REPO / "src" / "Original.cpp")

    job_dir = J.create_job("Original", out=str(tmp_path / "job"))
    candidate = job_dir / "candidate.cpp"
    candidate.write_text("//cpp\n// keep me\n", encoding="utf-8")
    first = json.loads((job_dir / "job.json").read_text(encoding="utf-8"))
    first["runtime_evidence"] = [{"path": "runtime/kept.json", "sha256": "abc"}]
    first["verification"] = {
        "verdict": "VERIFIED",
        "candidate_sha256": J._sha256(candidate.read_bytes()),
        "target": {"sha256": first["target"]["sha256"]},
    }
    J._write_json(job_dir / "job.json", first)
    J.create_job("Original", out=str(job_dir))
    job = json.loads((job_dir / "job.json").read_text(encoding="utf-8"))

    assert (job_dir / "target.bin").read_bytes() == b"\x01\x02\x03\x04"
    assert (job_dir / "source_snapshot.cpp").is_file()
    assert "keep me" in candidate.read_text(encoding="utf-8")
    assert job["source"]["candidate"]["seed"] == "preserved"
    assert job["runtime_evidence"][0]["path"] == "runtime/kept.json"
    assert job["verification"]["verdict"] == "VERIFIED"
    assert "linked-byte `VERIFIED`" in (job_dir / "TASK.md").read_text(encoding="utf-8")


def test_verify_requires_canonical_byte_and_link_match(tmp_path, monkeypatch):
    target = b"\x01\x02\x03\x04"
    _manifest(tmp_path, target)
    monkeypatch.setattr(J.M, "compile_c", lambda *_args, **_kwargs: b"object")
    monkeypatch.setattr(J, "_candidate_functions",
                        lambda _obj, _requested=None: ["Readable::Method"])
    monkeypatch.setattr(J.M, "extract_func",
                        lambda _obj, _symbol: (target, set()))
    monkeypatch.setattr(J.RA, "build_name_index", lambda: {})
    monkeypatch.setattr(J.LC, "linkcheck", lambda *_args, **_kwargs: {
        "name": "Original", "module": "arm9", "addr": "0x02004000",
        "verdict": "VERIFIED", "diffs": [], "blind": 0})

    result = J.verify_job(str(tmp_path))
    saved = json.loads((tmp_path / "verification.json").read_text(encoding="utf-8"))

    assert result["verdict"] == "VERIFIED"
    assert result["promotion_ready"] is True
    assert result["emitted_symbol"] == "Readable::Method"
    assert saved == result


def test_verify_rejects_loose_byte_match_with_blind_relocation(tmp_path, monkeypatch):
    target = b"\x01\x02\x03\x04"
    _manifest(tmp_path, target)
    monkeypatch.setattr(J.M, "compile_c", lambda *_args, **_kwargs: b"object")
    monkeypatch.setattr(J, "_candidate_functions", lambda *_args: ["Original"])
    monkeypatch.setattr(J.M, "extract_func",
                        lambda _obj, _symbol: (target, {0}))
    monkeypatch.setattr(J.RA, "build_name_index", lambda: {})
    monkeypatch.setattr(J.LC, "linkcheck", lambda *_args, **_kwargs: {
        "name": "Original", "module": "arm9", "addr": "0x02004000",
        "verdict": "BLIND-1", "diffs": [], "blind": 1})

    result = J.verify_job(str(tmp_path))

    assert result["byte_match"] is True
    assert result["verdict"] == "BLIND-1"
    assert result["promotion_ready"] is False
