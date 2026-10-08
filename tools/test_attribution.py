"""The author file is the credit record. Moving source does not come into it."""
import pathlib
import sys
import unittest

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import prepush_attribution as PA  # noqa: E402


class Compare(unittest.TestCase):
    def test_unchanged_file_passes(self):
        authors = {"arm9:0x02000000": "alice"}
        changed, lost, added = PA.compare(authors, authors)
        self.assertEqual((changed, lost, added), ([], [], []))

    def test_a_new_function_is_allowed(self):
        changed, lost, added = PA.compare(
            {"arm9:0x02000000": "alice"},
            {"arm9:0x02000000": "alice", "arm9:0x02000004": "bob"})
        self.assertEqual(changed, [])
        self.assertEqual(lost, [])
        self.assertEqual(added, [("arm9:0x02000004", "bob")])

    def test_changing_an_author_fails(self):
        changed, lost, added = PA.compare(
            {"arm9:0x02000000": "alice"},
            {"arm9:0x02000000": "bob"})
        self.assertEqual(changed, [("arm9:0x02000000", "alice", "bob")])
        self.assertEqual(lost, [])
        self.assertEqual(added, [])

    def test_deleting_an_author_fails(self):
        changed, lost, added = PA.compare(
            {"arm9:0x02000000": "alice"}, {})
        self.assertEqual(changed, [])
        self.assertEqual(lost, [("arm9:0x02000000", "alice")])
        self.assertEqual(added, [])


if __name__ == "__main__":
    unittest.main()
