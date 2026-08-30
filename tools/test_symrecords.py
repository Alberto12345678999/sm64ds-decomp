"""What the address join must and must not conclude, pinned in both directions.

symrecords exists because of a name-keyed join gone wrong (2026-08-30: an
"is this body sourced?" sweep read names out of one record and looked them up
against work keyed to the other, manufacturing phantom crack targets out of
matched, enrolled functions). Its restamp writes into symbols/verified.tsv, so
the negative half of every test matters more than the positive: a classifier
that upgrades a wrong-identity pair to "mechanical" would launder exactly the
class of error (#178 thunks, #774 dtors, the ov002/ov004 KillByAttack find)
that took byte-level evidence to dig out. Every guard here asserts the thing
that must still be refused next to the thing that may now be proposed.
"""
import pathlib
import tempfile
import unittest
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import symrecords as SR  # noqa: E402

TOOLS = pathlib.Path(__file__).resolve().parent


def rows_by_addr(config, verified):
    return {r["addr"]: r for r in SR.compare(config, verified)}


class AgreementIsInvisible(unittest.TestCase):
    def test_matching_name_produces_no_row(self):
        config = {0x100: [("arm9", "_ZN3FooD1Ev", "function")]}
        verified = {0x100: ("_ZN3FooD1Ev", "function")}
        self.assertEqual(SR.compare(config, verified), [])


class DtorEvidenceRules(unittest.TestCase):
    """The #774 lesson: dtor bodies are byte-identical across unrelated classes,
    so a lone dtor pair may not invent its own class-rename evidence."""

    DTOR = {0x100: [("arm9", "_ZN3NewD1Ev", "function")]}
    VDTOR = {0x100: ("_ZN3OldD2Ev", "function")}

    def test_uncorroborated_dtor_pair_is_identity(self):
        r = rows_by_addr(self.DTOR, self.VDTOR)["0x00000100"]
        self.assertEqual(r["verdict"], "identity")
        self.assertEqual(r["proposed"], "")

    def test_method_corroboration_unlocks_the_dtor(self):
        config = dict(self.DTOR)
        config[0x200] = [("arm9", "_ZN3New3RunEv", "function")]
        verified = dict(self.VDTOR)
        verified[0x200] = ("_ZN3Old3RunEv", "function")
        by = rows_by_addr(config, verified)
        self.assertEqual(by["0x00000200"]["verdict"], "class-rename")
        r = by["0x00000100"]
        self.assertEqual(r["verdict"], "class-rename+dtor-variant")
        self.assertEqual(r["proposed"], "_ZN3NewD1Ev")

    def test_contradicted_class_pair_proves_nothing(self):
        config = {0x200: [("arm9", "_ZN3New3RunEv", "function")],
                  0x300: [("arm9", "_ZN5Other4WalkEv", "function")]}
        verified = {0x200: ("_ZN3Old3RunEv", "function"),
                    0x300: ("_ZN3Old4WalkEv", "function")}
        by = rows_by_addr(config, verified)
        self.assertEqual(by["0x00000200"]["verdict"], "identity")
        self.assertEqual(by["0x00000300"]["verdict"], "identity")


class NestedNamesKeepTheirOuterClass(unittest.TestCase):
    """tools/demangle.py collapses `ActorBase::SceneNode::SceneNode()` and
    `fBase_c::SceneNode::SceneNode()` to the same qualified name; the classifier
    must still see the outer class move."""

    def test_uncorroborated_nested_ctor_is_identity(self):
        config = {0x100: [("arm9", "_ZN7fBase_c9SceneNodeC1Ev", "function")]}
        verified = {0x100: ("_ZN9ActorBase9SceneNodeC1Ev", "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertEqual(r["verdict"], "identity")
        self.assertEqual(r["proposed"], "")

    def test_corroborated_nested_ctor_is_a_class_rename(self):
        config = {0x100: [("arm9", "_ZN7fBase_c9SceneNodeC1Ev", "function")],
                  0x200: [("arm9", "_ZN7fBase_c9SceneNode7GetNextEv", "function")]}
        verified = {0x100: ("_ZN9ActorBase9SceneNodeC1Ev", "function"),
                    0x200: ("_ZN9ActorBase9SceneNode7GetNextEv", "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertEqual(r["verdict"], "class-rename")
        self.assertEqual(r["proposed"], "_ZN7fBase_c9SceneNodeC1Ev")


class ArgumentComparisons(unittest.TestCase):
    def test_substitution_spellings_compare_equal(self):
        # RNS_6SystemEb and RN8Particle6SystemEb are the same parameter list.
        config = {0x100: [("arm9",
                           "_ZN5dPa_c7level_c18fitWaterCallback_c8OnUpdateERN8Particle6SystemEb",
                           "function")]}
        verified = {0x100: ("_ZN8Particle16FitWaterCallback8OnUpdateERNS_6SystemEb",
                            "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertEqual(r["verdict"], "class-rename")

    def test_canonical_spelling_of_identical_signature(self):
        config = {0x100: [("arm9", "_ZN4cstd8__assertEPKcS1_S1_i", "function")]}
        verified = {0x100: ("_ZN4cstd8__assertEPKcPKcPKci", "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertEqual(r["verdict"], "canonical-spelling")
        self.assertEqual(r["proposed"], "_ZN4cstd8__assertEPKcS1_S1_i")

    def test_renamed_class_inside_args_is_not_a_signature_fix(self):
        config = {0x100: [("arm9", "_ZN6Camera10LookAtExitER8dActor_c", "function")],
                  0x200: [("arm9", "_ZN8dActor_c4TickEv", "function")]}
        verified = {0x100: ("_ZN6Camera10LookAtExitER5Actor", "function"),
                    0x200: ("_ZN5Actor4TickEv", "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertEqual(r["verdict"], "arg-rename")

    def test_unexplained_arg_change_stays_a_signature_fix(self):
        config = {0x100: [("arm9", "_ZN6Camera10LookAtExitER8dActor_c", "function")]}
        verified = {0x100: ("_ZN6Camera10LookAtExitER5Actor", "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertEqual(r["verdict"], "signature-fix")


class RefusalsAndAmbiguity(unittest.TestCase):
    def test_different_members_are_identity(self):
        config = {0x100: [("arm9", "_ZN1B3BarEv", "function")]}
        verified = {0x100: ("_ZN1A3FooEv", "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertEqual(r["verdict"], "identity")

    def test_thunkness_must_match(self):
        config = {0x100: [("arm9", "_ZN3FooD1Ev", "function")]}
        verified = {0x100: ("_ZThn80_N3FooD1Ev", "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertEqual(r["verdict"], "identity")

    def test_special_names_rename_with_corroboration_only(self):
        config = {0x100: [("arm9", "_ZTV8dActor_c", "data")],
                  0x200: [("arm9", "_ZN8dActor_c4TickEv", "function")]}
        verified = {0x100: ("_ZTV5Actor", "data"),
                    0x200: ("_ZN5Actor4TickEv", "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertEqual(r["verdict"], "class-rename")
        alone = rows_by_addr({0x100: config[0x100]}, {0x100: verified[0x100]})
        self.assertEqual(alone["0x00000100"]["verdict"], "identity")

    def test_operator_and_garbage_names_are_refused_not_guessed(self):
        self.assertIsNone(SR._parts("_ZN5dBgPiaSERKS_"))
        self.assertIsNone(
            SR._parts("_ZN9Animation17UpdateFileOffsets_ZN9AnimationER8BCA_File"))

    def test_two_real_names_across_overlays_propose_nothing(self):
        config = {0x100: [("ov002", "_ZN1A3FooEv", "function"),
                          ("ov004", "_ZN1B3FooEv", "function")]}
        verified = {0x100: ("_ZN1A3FooEv", "function")}
        self.assertEqual(SR.compare(config, verified), [])  # one module agrees
        verified = {0x100: ("_ZN1C3FooEv", "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertEqual(r["verdict"], "ambiguous-module")
        self.assertEqual(r["proposed"], "")


class OtherStates(unittest.TestCase):
    def test_placeholder_kind_mismatch_and_no_slot(self):
        config = {0x100: [("arm9", "func_00000100", "function")],
                  0x200: [("arm9", "STAR_MARKERS", "bss")]}
        verified = {0x100: ("_ZN3Foo3BarEv", "function"),
                    0x200: ("STAR_MARKERS", "data"),
                    0x300: ("Orphan", "function")}
        by = rows_by_addr(config, verified)
        self.assertEqual(by["0x00000100"]["state"], "CONFIG-PLACEHOLDER")
        self.assertEqual(by["0x00000200"]["state"], "KIND-MISMATCH")
        self.assertEqual(by["0x00000300"]["state"], "NO-SLOT")
        self.assertTrue(all(r["proposed"] == "" for r in by.values()))

    def test_relocated_spelling_is_noted_for_review(self):
        config = {0x100: [("arm9", "_ZN1B3FooEv", "function")],
                  0x900: [("ov004", "_ZN1A3FooEv", "function")]}
        verified = {0x100: ("_ZN1A3FooEv", "function")}
        r = rows_by_addr(config, verified)["0x00000100"]
        self.assertIn("0x00000900(ov004)", r["note"])


class RestampWritesOnlyThePlan(unittest.TestCase):
    def test_apply_rewrites_planned_rows_in_place(self):
        with tempfile.TemporaryDirectory() as td:
            repo = pathlib.Path(td)
            (repo / "symbols").mkdir()
            tsv = repo / "symbols" / "verified.tsv"
            tsv.write_text("0x00000100\t_ZN3OldD2Ev\tfunction\n"
                           "0x00000200\t_ZN3Old3RunEv\tfunction\n"
                           "0x00000300\tUntouched\tdata\n", encoding="utf-8")
            config = {0x100: [("arm9", "_ZN3NewD1Ev", "function")],
                      0x200: [("arm9", "_ZN3New3RunEv", "function")],
                      0x300: [("arm9", "Untouched", "data")]}
            plan = SR.restamp_plan(SR.compare(config, SR.load_verified(repo)))
            self.assertEqual(len(plan), 2)
            self.assertEqual(SR.apply_restamp(plan, repo), 2)
            self.assertEqual(tsv.read_text(encoding="utf-8"),
                             "0x00000100\t_ZN3NewD1Ev\tfunction\n"
                             "0x00000200\t_ZN3New3RunEv\tfunction\n"
                             "0x00000300\tUntouched\tdata\n")


class OnlyAllowlistedToolsOpenTheImportMirror(unittest.TestCase):
    """The policy half of the incident fix: nothing new joins the records by
    name because nothing new reads verified.tsv at all -- a tool that wants
    both records goes through symrecords' address-keyed API. If this test
    just failed on a file you added, import symrecords instead of opening
    symbols/verified.tsv, or make the case for the allowlist in review."""

    ALLOWED = {"import_symbols.py",   # writes the mirror; the importer itself
               "symrecords.py",       # the address join this test protects
               "test_symrecords.py",
               "cpp_rename.py",       # pre-dates the rule; address-keyed reader
               "cluster_targets.py"}  # pre-dates the rule; address-keyed reader

    def test_no_new_direct_readers(self):
        offenders = sorted(
            p.name for p in TOOLS.glob("*.py")
            if p.name not in self.ALLOWED
            and "verified.tsv" in p.read_text(encoding="utf-8", errors="ignore"))
        self.assertEqual(offenders, [])


class LiveTreeInvariants(unittest.TestCase):
    def test_verified_rows_are_unique_and_three_column(self):
        seen = set()
        text = (TOOLS.parent / "symbols" / "verified.tsv").read_text(encoding="utf-8")
        for line in text.splitlines():
            parts = line.split("\t")
            self.assertEqual(len(parts), 3, line)
            addr = int(parts[0], 16)
            self.assertNotIn(addr, seen, f"duplicate address {parts[0]}")
            seen.add(addr)

    def test_config_load_covers_the_module_universe(self):
        config = SR.load_config()
        labels = {mod for entries in config.values() for mod, _n, _k in entries}
        self.assertIn("arm9", labels)
        self.assertIn("itcm", labels)   # the module four tools once dropped
        # 106 modules exist; a handful carry no symbol rows at all, so the count
        # of modules that DO is what a silent parsing regression would dent.
        self.assertGreater(len(labels), 90)


if __name__ == "__main__":
    unittest.main()
