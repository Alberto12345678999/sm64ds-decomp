"""The per-function tier columns chaos_db_ci publishes: converted, linked, class, tuId, tuState.

The headline numbers in stats.tiers are old and have their own tests. What is new is that the
same facts now ride on every function record, and the failure that matters is the two
disagreeing: an Atlas that paints 4,500 tiles "converted" under a bar that says 4,531. So the
first class pins the per-symbol readings to the headline on the real tree, and the rest pin the
sparse-column contract (a key is present only when true or known) and the one refusal that keeps
two port builds from mixing in one file.
"""
import json
import pathlib
import sys
import tempfile
import unittest

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import chaos_db_ci as CDB  # noqa: E402
import tiers  # noqa: E402

REPO = pathlib.Path(__file__).resolve().parent.parent


class ConvertedPerSymbolMatchesTheHeadline(unittest.TestCase):
    """converted(per_symbol=True) is the headline's own readings, not a second opinion."""

    @classmethod
    def setUpClass(cls):
        cls.plain = tiers.converted()
        cls.detail = tiers.converted(per_symbol=True)

    def test_default_call_is_unchanged(self):
        self.assertNotIn("by_symbol", self.plain)

    def test_headline_is_identical_with_or_without_the_breakdown(self):
        d = {k: v for k, v in self.detail.items() if k != "by_symbol"}
        self.assertEqual(d, self.plain)

    def test_true_readings_sum_to_the_headline(self):
        n = sum(1 for syms in self.detail["by_symbol"].values() for ok in syms.values() if ok)
        self.assertEqual(n, self.plain["converted"])

    def test_every_source_owned_function_has_a_reading(self):
        n = sum(len(syms) for syms in self.detail["by_symbol"].values())
        self.assertEqual(n, self.plain["functions"])


class ClassOf(unittest.TestCase):
    def test_a_method_has_its_class(self):
        self.assertEqual(CDB.class_of("_ZN10dMgPsOpt_c5CloseEv"), "dMgPsOpt_c")

    def test_a_destructor_has_its_class(self):
        self.assertEqual(CDB.class_of("_ZN8dActor_cD0Ev"), "dActor_c")

    def test_a_namespace_counts_as_the_owner(self):
        self.assertEqual(CDB.class_of("_ZN2GX13SetBankForTexEt"), "GX")

    def test_a_nested_owner_keeps_its_outer_scope(self):
        self.assertEqual(CDB.class_of("_ZN5Sound6Player21SetPlayableSeqCountEi"),
                         "Sound::Player")

    def test_a_thunk_names_the_class_it_adjusts(self):
        self.assertEqual(CDB.class_of("_ZThn80_N9ModelAnimD0Ev"), "ModelAnim")

    def test_placeholders_and_c_names_have_no_owner(self):
        for n in ("func_02011654", "func_ov006_020f15ac", "_dmul", "__aeabi_idiv", "memcpy"):
            self.assertIsNone(CDB.class_of(n), n)

    def test_a_free_mangled_function_has_no_owner(self):
        self.assertIsNone(CDB.class_of("_Z4Funcv"))

    def test_vague_linkage_data_has_no_owner(self):
        self.assertIsNone(CDB.class_of("_ZTV8dActor_c"))


class Scratch(unittest.TestCase):
    """A throwaway REPO for the readers that take their inputs from config/."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = pathlib.Path(self.tmp.name)
        self.addCleanup(self.tmp.cleanup)
        (self.root / "config").mkdir()
        saved = CDB.REPO
        CDB.REPO = self.root
        self.addCleanup(lambda: setattr(CDB, "REPO", saved))

    def stamp(self, commit="abc1234"):
        (self.root / "config" / "port_linkage.json").write_text(json.dumps({
            "linkedTus": 2, "matchedTus": 3, "measuredAt": "2026-10-16",
            "branch": "port/x", "commit": commit}), encoding="utf-8")

    def listing(self, commit="abc1234", keys=("arm9:0x02000000", "ov001:0x02100000")):
        (self.root / "config" / "port_linked_functions.txt").write_text(
            "# header\n# commit: " + commit + "\n" + "\n".join(keys) + "\n", encoding="utf-8")


class LinkedList(Scratch):
    def test_a_list_from_the_stamped_build_is_believed(self):
        self.stamp()
        self.listing()
        self.assertEqual(CDB.linked_functions(), {"arm9:0x02000000", "ov001:0x02100000"})

    def test_a_list_from_another_build_is_ignored(self):
        self.stamp("abc1234")
        self.listing("def5678")
        self.assertIsNone(CDB.linked_functions())

    def test_a_list_with_no_stamp_is_ignored(self):
        self.listing()
        self.assertIsNone(CDB.linked_functions())

    def test_a_stamp_with_no_provenance_does_not_vouch_for_a_list(self):
        (self.root / "config" / "port_linkage.json").write_text(
            json.dumps({"linkedTus": 2, "matchedTus": 3}), encoding="utf-8")
        self.listing()
        self.assertIsNone(CDB.linked_functions())

    def test_no_list_means_no_column(self):
        self.stamp()
        self.assertIsNone(CDB.linked_functions())


class UnitIndex(Scratch):
    def entry(self, name, module, status, addrs):
        d = self.root / "config" / "tu_manifest.d" / module
        d.mkdir(parents=True, exist_ok=True)
        (d / f"{name}.json").write_text(json.dumps({
            "id": f"{module}/{name}", "module": module, "status": status,
            "functions": [{"symbol": f"s{a}", "address": hex(a), "size": "0x4"} for a in addrs],
        }), encoding="utf-8")

    def test_a_function_gets_its_units_id_and_state(self):
        self.entry("Actor", "arm9", "promoted", [0x2000000, 0x2000010])
        self.entry("Other", "ov001", "text-verified", [0x2100000])
        idx = CDB.unit_index()
        self.assertEqual(idx[("arm9", 0x2000000)], ("arm9/Actor", "promoted"))
        self.assertEqual(idx[("arm9", 0x2000010)], ("arm9/Actor", "promoted"))
        self.assertEqual(idx[("ov001", 0x2100000)], ("ov001/Other", "text-verified"))

    def test_the_same_address_in_another_module_is_another_function(self):
        self.entry("Actor", "arm9", "promoted", [0x2000000])
        self.assertNotIn(("ov001", 0x2000000), CDB.unit_index())

    def test_no_manifest_is_an_empty_index(self):
        self.assertEqual(CDB.unit_index(), {})

    def test_an_entry_missing_its_state_is_skipped_not_fatal(self):
        d = self.root / "config" / "tu_manifest.d" / "arm9"
        d.mkdir(parents=True)
        (d / "x.json").write_text(json.dumps({"id": "arm9/x", "module": "arm9",
                                              "functions": [{"address": "0x2000000"}]}),
                                  encoding="utf-8")
        self.assertEqual(CDB.unit_index(), {})


class CommittedListAgreesWithTheStamp(unittest.TestCase):
    """The tripwire for a hand-refreshed stamp. chaos_db_ci would only LOG that it ignored a
    list from another build, and a quiet missing column is how an Atlas goes grey for weeks."""

    def test_the_committed_files_describe_one_build(self):
        listing = REPO / "config" / "port_linked_functions.txt"
        if not listing.is_file():
            self.skipTest("no committed per-function list")
        stamp = tiers.linked()
        self.assertIsNotNone(stamp, "config/port_linkage.json has no usable stamp")
        header = {}
        for line in listing.read_text(encoding="utf-8").splitlines():
            if line.startswith("# ") and ": " in line:
                k, v = line[2:].split(": ", 1)
                header[k] = v
        self.assertEqual(header.get("commit"), stamp["commit"],
                         "config/port_linked_functions.txt and config/port_linkage.json come from "
                         "different port builds; re-run tools/port_linked_functions.py --stamp")
        self.assertEqual(header.get("branch"), stamp["branch"])
        self.assertEqual(int(header["linkedTus"]), stamp["linked"])
        self.assertEqual(int(header["matchedTus"]), stamp["matchedTus"])

    def test_every_key_is_a_module_and_an_address(self):
        listing = REPO / "config" / "port_linked_functions.txt"
        if not listing.is_file():
            self.skipTest("no committed per-function list")
        import re
        key = re.compile(r"^(arm9|itcm|ov\d{3}):0x[0-9a-f]{8}$")
        keys = [l for l in listing.read_text(encoding="utf-8").splitlines()
                if l and not l.startswith("#")]
        self.assertTrue(keys)
        self.assertEqual(len(keys), len(set(keys)), "duplicate keys")
        self.assertEqual(keys, sorted(keys), "the list is written sorted")
        bad = [k for k in keys if not key.match(k)]
        self.assertEqual(bad[:5], [])


if __name__ == "__main__":
    unittest.main()
