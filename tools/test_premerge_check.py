#!/usr/bin/env python3
"""Tests for tools/premerge_check.py.

EVERY TEST IN HERE RUNS WITH NO GIT, NO `gh`, NO COMPILER AND NO `extracted/`.
That is a requirement of the suite, not an accident of what was easy to write. This
repository has shipped a gate that reported a clean tree after its match count had
silently gone to zero, and the general shape of that defect is a test file that
self-`return`s when its inputs are missing: the suite passes, CI is green, and the
thing under test has not been exercised at all. So the logic that decides the exit
code -- the verdict diff, the coverage delta, the merge-tree parse and the PR
resolution failures -- is written as pure functions over data, and tested as such.

The one test that genuinely needs a git binary calls `self.skipTest` and says why.
A real skip is visible in the runner's output. A bare `return` is not, and would let
this file report a pass on a machine where it checked nothing.

    python -m unittest tools.test_premerge_check -v
"""
import json
import pathlib
import subprocess
import sys
import unittest

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))

import premerge_check as P  # noqa: E402


class ClassifyTests(unittest.TestCase):
    """The four verdict pairs. This is the whole exit-code contract."""

    def test_green_green_is_ok(self):
        self.assertEqual(P.classify("pass", "pass"), "ok")

    def test_green_red_is_the_regression(self):
        self.assertEqual(P.classify("pass", "fail"), "REGRESSION")

    def test_red_red_is_not_this_prs_fault(self):
        # The load-bearing one. A gate already broken on the base must never be
        # charged to a PR that merely merges against it.
        self.assertEqual(P.classify("fail", "fail"), "pre-existing")

    def test_red_green_is_a_fix(self):
        self.assertEqual(P.classify("fail", "pass"), "fixed")

    def test_error_counts_as_red_on_the_merge_side(self):
        # A gate that could not RUN on the merge result is a fact about the merge
        # result. Treating exit 2 as a pass is how a gate stops meaning anything.
        self.assertEqual(P.classify("pass", "error"), "REGRESSION")

    def test_error_on_both_sides_is_pre_existing(self):
        self.assertEqual(P.classify("error", "error"), "pre-existing")


class DiffVerdictTests(unittest.TestCase):
    def test_rows_cover_the_union_and_only_green_red_regresses(self):
        base = {"a": {"status": "pass"}, "b": {"status": "fail"},
                "c": {"status": "fail"}, "d": {"status": "pass"}}
        merge = {"a": {"status": "pass"}, "b": {"status": "fail"},
                 "c": {"status": "pass"}, "d": {"status": "fail"}}
        rows = P.diff_verdicts(base, merge)
        got = {r["gate"]: r["verdict"] for r in rows}
        self.assertEqual(got, {"a": "ok", "b": "pre-existing",
                               "c": "fixed", "d": "REGRESSION"})
        self.assertEqual([r["gate"] for r in P.regressions(rows)], ["d"])

    def test_a_gate_that_vanishes_from_the_merge_result_is_a_regression(self):
        # `absent` is not `pass`. A gate dropping out of the merge result's run --
        # because the tool it names was deleted by one of the merged commits -- is a
        # thing to be told about, not a row that quietly disappears from the table.
        rows = P.diff_verdicts({"a": {"status": "pass"}}, {})
        self.assertEqual(rows, [{"gate": "a", "base": "pass", "merge": "absent",
                                 "verdict": "REGRESSION"}])

    def test_a_gate_only_the_merge_result_has_is_not_a_regression(self):
        rows = P.diff_verdicts({}, {"a": {"status": "pass"}})
        self.assertEqual(rows[0]["verdict"], "fixed")

    def test_no_gates_at_all_yields_no_regressions(self):
        self.assertEqual(P.diff_verdicts({}, {}), [])


class CoverageDeltaTests(unittest.TestCase):
    BASE = {"currentBytes": 2066772, "entries": 11025, "modules": 74,
            "bySection": {".text": 1941060, ".init": 125712}}

    def test_identical_trees_report_nothing(self):
        self.assertEqual(P.coverage_regressions(self.BASE, dict(self.BASE)), [])

    def test_growth_is_silent(self):
        m = json.loads(json.dumps(self.BASE))
        m["currentBytes"] += 4028
        m["bySection"][".text"] += 4028
        self.assertEqual(P.coverage_regressions(self.BASE, m), [])

    def test_a_byte_loss_is_named_with_both_numbers(self):
        m = json.loads(json.dumps(self.BASE))
        m["currentBytes"] -= 4028
        lines = P.coverage_regressions(self.BASE, m)
        self.assertEqual(len(lines), 1)
        self.assertIn("2066772 -> 2062744", lines[0])
        self.assertIn("-4028", lines[0])

    def test_a_section_disappearing_is_a_decrease_to_zero(self):
        # The shape of a delinks entry deleted outright: layout_check reports that
        # as INFO and can never fail on it, so it has to be caught by the byte set.
        m = json.loads(json.dumps(self.BASE))
        del m["bySection"][".init"]
        lines = P.coverage_regressions(self.BASE, m)
        self.assertEqual(lines, ["bySection[.init]: 125712 -> 0 (-125712)"])

    def test_a_new_section_is_not_a_regression(self):
        m = json.loads(json.dumps(self.BASE))
        m["bySection"][".rodata"] = 512
        self.assertEqual(P.coverage_regressions(self.BASE, m), [])

    def test_unmeasured_side_reports_nothing_rather_than_guessing(self):
        # None means "could not be measured". Subtracting from a missing number and
        # calling the answer a regression would blame a PR for a broken export.
        self.assertEqual(P.coverage_regressions(None, self.BASE), [])
        self.assertEqual(P.coverage_regressions(self.BASE, None), [])

    def test_a_tu_promotion_is_not_a_regression(self):
        # The measured false positive. PR #2024 as it actually stood on 2026-08-30:
        # `entries` 11025 -> 11017, every byte total unchanged. Thirty-eight
        # per-function delinks entries becoming three merged ones covering the same
        # address range is the WHOLE POINT of TU promotion, and an earlier draft of
        # this tool called it red on two open PRs in its first real run.
        m = json.loads(json.dumps(self.BASE))
        m["entries"] = 11017
        self.assertEqual(P.coverage_regressions(self.BASE, m), [])

    def test_modules_falling_is_also_not_a_regression(self):
        m = json.loads(json.dumps(self.BASE))
        m["modules"] -= 1
        self.assertEqual(P.coverage_regressions(self.BASE, m), [])


class CoverageContextTests(unittest.TestCase):
    """`entries`/`modules` are reported, and can never fail a run."""

    BASE = CoverageDeltaTests.BASE

    def test_flat_numbers_produce_no_noise(self):
        self.assertEqual(P.coverage_context(self.BASE, dict(self.BASE)), [])

    def test_an_entry_drop_with_flat_bytes_is_labelled_a_consolidation(self):
        m = json.loads(json.dumps(self.BASE))
        m["entries"] = 11017
        lines = P.coverage_context(self.BASE, m, byte_regressions=[])
        self.assertEqual(len(lines), 1)
        self.assertIn("11025 -> 11017", lines[0])
        self.assertIn("-8", lines[0])
        self.assertIn("consolidation", lines[0])

    def test_the_reassurance_is_withdrawn_when_bytes_fell_too(self):
        # If the byte set really shrank, the entry drop is corroborating a loss and
        # must not be dressed up as a consolidation.
        m = json.loads(json.dumps(self.BASE))
        m["entries"] = 11017
        m["currentBytes"] -= 4028
        byte_lines = P.coverage_regressions(self.BASE, m)
        self.assertTrue(byte_lines)
        lines = P.coverage_context(self.BASE, m, byte_regressions=byte_lines)
        self.assertEqual(len(lines), 1)
        self.assertNotIn("consolidation", lines[0])

    def test_growth_is_reported_without_a_consolidation_note(self):
        m = json.loads(json.dumps(self.BASE))
        m["entries"] += 12
        lines = P.coverage_context(self.BASE, m)
        self.assertEqual(len(lines), 1)
        self.assertIn("+12", lines[0])
        self.assertNotIn("consolidation", lines[0])

    def test_unmeasured_side_reports_nothing(self):
        self.assertEqual(P.coverage_context(None, self.BASE), [])
        self.assertEqual(P.coverage_context(self.BASE, None), [])

    def test_context_keys_and_byte_keys_do_not_overlap(self):
        # If a key were in both lists it could fail a run through the byte path
        # while being explained away as context in the same table.
        self.assertEqual(set(P.COVERAGE_BYTE_KEYS) & set(P.COVERAGE_CONTEXT_KEYS),
                         set())
        self.assertIn("currentBytes", P.COVERAGE_BYTE_KEYS)
        self.assertIn("entries", P.COVERAGE_CONTEXT_KEYS)


class MergeTreeParseTests(unittest.TestCase):
    OID = "c40335b6578cecbd313b241d50fc5fab8ca6fa12"

    def test_clean_merge_yields_a_tree_and_no_conflicts(self):
        tree, conflicts = P.parse_merge_tree(0, self.OID + "\n")
        self.assertEqual(tree, self.OID)
        self.assertEqual(conflicts, [])

    def test_conflict_is_its_own_outcome_not_a_gate_failure(self):
        out = (self.OID + "\n"
               "100644 aaa 1\tsrc/Foo.cpp\n"
               "100644 bbb 2\tsrc/Foo.cpp\n"
               "\nAuto-merging src/Foo.cpp\nCONFLICT (content): src/Foo.cpp\n")
        tree, conflicts = P.parse_merge_tree(1, out)
        self.assertEqual(tree, self.OID)
        self.assertTrue(conflicts)
        self.assertTrue(any("CONFLICT" in c for c in conflicts))

    def test_conflict_with_no_detail_still_reports_a_conflict(self):
        tree, conflicts = P.parse_merge_tree(1, self.OID + "\n")
        self.assertEqual(conflicts, ["conflict (no detail reported)"])

    def test_git_refusing_to_answer_is_neither_clean_nor_a_conflict(self):
        # conflicts is None -- the caller must report a TOOL ERROR. Reporting an
        # unresolvable ref as "this PR conflicts" would be a lie about the PR.
        tree, conflicts = P.parse_merge_tree(128, "")
        self.assertIsNone(tree)
        self.assertIsNone(conflicts)

    def test_exit_zero_with_no_oid_is_not_silently_a_clean_merge(self):
        tree, conflicts = P.parse_merge_tree(0, "")
        self.assertIsNone(tree)
        self.assertTrue(conflicts)


class PrNumberTests(unittest.TestCase):
    def test_what_counts_as_a_pr_number(self):
        for spec in ("2001", "#2001", " 2001 "):
            self.assertTrue(P.is_pr_number(spec), spec)
        for spec in ("origin/main", "487ba140e", "HEAD", "v1.2", "20a1"):
            self.assertFalse(P.is_pr_number(spec), spec)


class _Runner:
    """A stand-in for subprocess.run, so the gh failure paths need no gh."""

    def __init__(self, *, raises=None, rc=0, stdout="", stderr=""):
        self.raises, self.rc = raises, rc
        self.stdout, self.stderr = stdout, stderr
        self.calls = []

    def __call__(self, argv, **kw):
        self.calls.append(argv)
        if self.raises:
            raise self.raises
        return subprocess.CompletedProcess(argv, self.rc, self.stdout, self.stderr)


class ResolvePrTests(unittest.TestCase):
    """Every one of these is a sentence a person reads, not a traceback."""

    def test_success_returns_the_head_sha_and_a_label(self):
        r = _Runner(stdout=json.dumps({"headRefOid": "a" * 40,
                                       "title": "Convert daKrb_c",
                                       "state": "OPEN", "baseRefName": "main"}))
        sha, label = P.resolve_pr("#2001", runner=r)
        self.assertEqual(sha, "a" * 40)
        self.assertIn("#2001", label)
        self.assertIn("daKrb_c", label)
        self.assertEqual(r.calls[0][:4], ["gh", "pr", "view", "2001"])

    def test_gh_not_installed_says_so_and_offers_the_way_round_it(self):
        r = _Runner(raises=FileNotFoundError())
        with self.assertRaises(ValueError) as ctx:
            P.resolve_pr("2001", runner=r)
        msg = str(ctx.exception)
        self.assertIn("not on PATH", msg)
        self.assertIn("head sha", msg)   # the workaround, not just the complaint

    def test_gh_unauthenticated_surfaces_ghs_own_last_line(self):
        r = _Runner(rc=1, stderr="gh: To use GitHub CLI, run: gh auth login\n")
        with self.assertRaises(ValueError) as ctx:
            P.resolve_pr("2001", runner=r)
        self.assertIn("gh auth login", str(ctx.exception))

    def test_gh_failing_with_no_stderr_still_says_something_useful(self):
        r = _Runner(rc=4, stderr="")
        with self.assertRaises(ValueError) as ctx:
            P.resolve_pr("2001", runner=r)
        self.assertIn("gh exited 4", str(ctx.exception))

    def test_unparseable_output_is_an_error_not_a_crash(self):
        r = _Runner(stdout="not json at all")
        with self.assertRaises(ValueError) as ctx:
            P.resolve_pr("2001", runner=r)
        self.assertIn("no usable JSON", str(ctx.exception))

    def test_json_without_a_head_sha_is_an_error(self):
        r = _Runner(stdout=json.dumps({"title": "x"}))
        with self.assertRaises(ValueError) as ctx:
            P.resolve_pr("2001", runner=r)
        self.assertIn("no headRefOid", str(ctx.exception))

    def test_os_error_running_gh_is_an_error_not_a_crash(self):
        r = _Runner(raises=OSError("permission denied"))
        with self.assertRaises(ValueError) as ctx:
            P.resolve_pr("2001", runner=r)
        self.assertIn("permission denied", str(ctx.exception))


class GateShapeTests(unittest.TestCase):
    """Properties of the gate table itself, checkable without running anything."""

    FORBIDDEN = ("rombuild", "eligible")

    def test_no_gate_can_ever_invoke_a_rom_build(self):
        # `build/` is shared between worktrees here, so a gate that needed a ROM
        # build could not run alongside the work it gates. This asserts the rule
        # rather than trusting the docstring to keep being true.
        for gate in P.GATES:
            try:
                cmds = gate["commands"]("/nonexistent")
            except Exception:
                continue          # needs a real tree; covered by the end-to-end test
            for argv in cmds or []:
                joined = " ".join(argv)
                for bad in self.FORBIDDEN:
                    self.assertNotIn(bad, joined, gate["key"])

    def test_every_gate_names_an_existing_tool(self):
        repo = pathlib.Path(__file__).resolve().parent.parent
        for gate in P.GATES:
            try:
                cmds = gate["commands"]("/nonexistent")
            except Exception:
                continue
            for argv in cmds or []:
                script = argv[1]
                self.assertTrue((repo / script).is_file(),
                                f"{gate['key']} names {script}, which is not there")

    def test_a_gate_with_nothing_to_do_is_an_error_not_a_pass(self):
        # The anti-hollow rule, at the level this tool controls: header-offsets over
        # zero headers must not read as green.
        res = P.run_gate({"key": "empty", "commands": lambda t: []}, "/nonexistent")
        self.assertEqual(res["status"], "error")
        self.assertIn("empty input set", res["summary"])

    def test_a_gate_whose_command_builder_raises_is_an_error_not_a_pass(self):
        def boom(_tree):
            raise RuntimeError("index unreadable")
        res = P.run_gate({"key": "boom", "commands": boom}, "/nonexistent")
        self.assertEqual(res["status"], "error")
        self.assertIn("index unreadable", res["summary"])

    def test_a_gate_that_cannot_be_launched_is_an_error_not_a_pass(self):
        res = P.run_gate(
            {"key": "nope",
             "commands": lambda t: [["definitely-not-a-real-binary-xyz"]]},
            pathlib.Path(__file__).resolve().parent)
        self.assertEqual(res["status"], "error")


class SummariseTests(unittest.TestCase):
    """Which line of a gate's output a reader is shown."""

    def test_a_passing_gate_is_summarised_by_its_last_line(self):
        self.assertEqual(
            P.summarise(["scanning...", "CONVERTED ratchet PASS   baseline 2553"],
                        "pass"),
            "CONVERTED ratchet PASS   baseline 2553")

    def test_a_red_batched_gate_reports_the_complaint_not_the_last_line(self):
        # header-offsets prints one line per header and ends on whichever sorted
        # last, which says nothing about why it failed.
        lines = ["include/A.h: 0 commented fields, 0 mismatched, 0 unparsed",
                 "include/B.h: 12 commented fields, 3 mismatched, 0 unparsed",
                 "include/Z.h: 0 commented fields, 0 mismatched, 0 unparsed"]
        self.assertIn("B.h", P.summarise(lines, "fail"))

    def test_zero_mismatched_is_not_read_as_a_complaint(self):
        lines = ["include/A.h: 0 commented fields, 0 mismatched, 0 unparsed",
                 "check: something else went wrong"]
        # No `[1-9]\\d* mismatched` anywhere, so the fallback (last line) is used.
        self.assertEqual(P.summarise(lines, "fail"),
                         "check: something else went wrong")

    def test_no_output_at_all_says_so(self):
        self.assertEqual(P.summarise([], "fail"), "(no output)")


class ExportTreeTests(unittest.TestCase):
    """The one place a real git binary is genuinely required."""

    def test_exported_tree_answers_git_ls_files(self):
        try:
            subprocess.run(["git", "--version"], capture_output=True, check=True)
        except (OSError, subprocess.CalledProcessError):
            self.skipTest("no git binary on PATH -- the export step cannot be "
                          "exercised here (the pure logic above still was)")
        repo = pathlib.Path(__file__).resolve().parent.parent
        head = subprocess.run(["git", "-C", str(repo), "rev-parse", "HEAD^{tree}"],
                              capture_output=True, text=True)
        if head.returncode != 0:
            self.skipTest("tools/ is not inside a git repository with a HEAD")
        import tempfile
        with tempfile.TemporaryDirectory(prefix="premerge-test-") as tmp:
            dest = pathlib.Path(tmp) / "tree"
            P.export_tree(repo, head.stdout.strip(), dest, tmp)
            # The whole point of the `git init` + index copy: a plain
            # `checkout-index --prefix=` export exits 128 on this command, and four
            # of the gates shell out to exactly it.
            out = subprocess.run(["git", "-C", str(dest), "ls-files", "tools/*.py"],
                                 capture_output=True, text=True)
            self.assertEqual(out.returncode, 0, out.stderr)
            # Assert on a file the export is guaranteed to carry. Not this file: the
            # export is of HEAD^{tree}, so an uncommitted premerge_check.py is
            # legitimately absent and asserting on it would fail for the wrong reason.
            self.assertIn("tools/tiers_ratchet.py", out.stdout)
            self.assertTrue((dest / "tools" / "tiers_ratchet.py").is_file())


if __name__ == "__main__":
    unittest.main(verbosity=2)
