"""Pinned linker semantics and fail-closed validation of generated LCF policy."""
import io
import pathlib
import struct
import subprocess
import tempfile
import unittest

from elftools.elf.elffile import ELFFile
import linker_alignment as LA
import tubuild as TB


def script(body="ALIGNALL(4); sample.o(.data)", region="TEST"):
    return (f"MEMORY {{\n {region} : ORIGIN = 0x1000 > test.bin\n}}\n"
            f"SECTIONS {{\n .test : {{ {body} }} > {region}\n}}\n")


class PolicyTests(unittest.TestCase):
    def verify(self, text):
        with tempfile.TemporaryDirectory() as directory:
            path = pathlib.Path(directory) / "test.lcf"
            path.write_text(text, encoding="utf-8")
            return LA.verify_lcf(path)

    def test_generated_policy(self):
        self.assertEqual(self.verify(script()), {"inputAlignment": 4, "outputs": ["TEST"]})

    def test_comments_are_not_directives(self):
        self.assertEqual(self.verify(script("/* ALIGNALL(1); */ ALIGNALL(4); sample.o(.data)"))["inputAlignment"], 4)
        with self.assertRaises(ValueError):
            self.verify(script("/* ALIGNALL(4); */ sample.o(.data)"))

    def test_policy_drift_refused(self):
        for body in ("sample.o(.data)", "ALIGNALL(1); sample.o(.data)",
                     "sample.o(.data) ALIGNALL(4);", "ALIGNALL(4); sample.o(.data) ALIGNALL(4);",
                     "ALIGNALL(4); sample.o(.data) ALIGNALL(8);", "// ALIGNALL(4);\nsample.o(.data)"):
            with self.subTest(body=body), self.assertRaises(ValueError):
                self.verify(script(body))

    def test_missing_duplicate_or_unknown_outputs_refused(self):
        valid = script()
        invalid = [valid.replace(".test :", ".test INVALID :"),
                   valid.replace("} > TEST", "} > OTHER"),
                   valid.replace("SECTIONS {", "SECTIONS { .other : { ALIGNALL(4); } > TEST"),
                   valid.replace("SECTIONS {", "SECTIONS { .test : { ALIGNALL(4); } > OTHER"),
                   valid.replace("test.bin", "test.bin\n EXTRA : ORIGIN = 0x2000 > extra.bin"),
                   valid.replace("test.bin", "test.bin\n TEST : ORIGIN = 0x2000 > duplicate.bin"),
                   valid.replace("SECTIONS {", "ALIGNALL(4); SECTIONS {"),
                   "SECTIONS { .test : { ALIGNALL(4); } > TEST }"]
        for text in invalid:
            with self.subTest(text=text), self.assertRaises(ValueError):
                self.verify(text)

    def test_minimum_preserves_greater_alignment(self):
        self.assertEqual([LA.effective_alignment(a) for a in (0, 1, 2, 4, 8, 16, 32)],
                         [4, 4, 4, 4, 8, 16, 32])

    def test_control_fingerprint_binds_alignment_policy(self):
        policy = pathlib.Path(LA.__file__).resolve()
        self.assertIn(policy, [path.resolve() for path in TB.BASELINE_CONTROL_TOOLS])
        with tempfile.TemporaryDirectory() as directory:
            copied = []
            for source in TB.BASELINE_CONTROL_TOOLS:
                target = pathlib.Path(directory) / source.name
                target.write_bytes(source.read_bytes())
                copied.append(target)
            before = TB.content_files_sha256(copied)
            target = pathlib.Path(directory) / policy.name
            target.write_bytes(target.read_bytes() + b"\n# simulated policy drift\n")
            self.assertNotEqual(before, TB.content_files_sha256(copied))


class NativeLinkerTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not (TB.RB.MW / TB.RB.VERSION / "mwccarm.exe").is_file():
            raise unittest.SkipTest("pinned private compiler is unavailable")
        (TB.REPO / "build").mkdir(exist_ok=True)
        cls.directory = tempfile.TemporaryDirectory(prefix="linker-align-", dir=TB.REPO / "build")
        cls.root = pathlib.Path(cls.directory.name)
        source = cls.root / "sample.cpp"
        source.write_text('//cpp\nextern "C" const char * const names[] = {"Cave", "Suisou", "Fire Mt"};\n'
                          'extern "C" short values[3] = {1,2,3};\n'
                          'extern "C" unsigned char wide[3] __attribute__((aligned(16))) = {1,2,3};\n', encoding="utf-8")
        cls.obj = TB.M.compile_c(source, TB.RB.VERSION, TB.BP.flags_for(TB.REPO / "src/game/stages/d_s_title.cpp"))
        assert cls.obj
        (cls.root / "sample.o").write_bytes(cls.obj)

    @classmethod
    def tearDownClass(cls):
        cls.directory.cleanup()

    def linked(self, alignment):
        lcf = self.root / f"align{alignment}.lcf"
        lcf.write_text(script(f"ALIGNALL({alignment}); sample.o(.data) sample.o(.rodata)"), encoding="utf-8")
        output = self.root / f"align{alignment}.elf"
        command = [*TB.RB.launcher(), str(TB.RB.MW / TB.RB.LD_VERSION / "mwldarm.exe"),
                   "-proc", "arm946e", "-nostdlib", "-interworking", "-m", "", "-nodead", "-msgstyle", "gcc",
                   str(self.root / "sample.o"), str(lcf), "-o", str(output)]
        result = subprocess.run(command, cwd=self.root, capture_output=True, text=True, encoding="utf-8")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return ELFFile(io.BytesIO(output.read_bytes())), (self.root / "test.bin").read_bytes()

    def test_real_linker_addresses_bytes_and_relocations(self):
        elf = ELFFile(io.BytesIO(self.obj))
        alignments = {s["sh_addralign"] for s in elf.iter_sections() if s.name == ".data"}
        self.assertTrue({1, 2, 16}.issubset(alignments))
        linked, binary = self.linked(4)
        symbols = {s.name: s["st_value"] for s in linked.get_section_by_name(".symtab").iter_symbols()}
        cursor = 0x1000
        for name in (".data", ".rodata"):
            cursor = (cursor + 3) & ~3
            layout, error = TB.section_contribution(self.obj, name, cursor)
            self.assertIsNone(error)
            for symbol, row in layout["symbols"].items():
                self.assertEqual(row["address"], symbols[symbol])
            body = bytearray(layout["bytes"])
            for relocation in layout["relocs"]:
                self.assertEqual(relocation["type"], 2)
                struct.pack_into("<I", body, relocation["offset"],
                                 symbols[relocation["symbol"]] + relocation["addend"])
            offset = cursor - 0x1000
            self.assertEqual(bytes(body), binary[offset:offset + len(body)])
            cursor += len(body)
        compact, _ = self.linked(1)
        compact_symbols = {s.name: s["st_value"] for s in compact.get_section_by_name(".symtab").iter_symbols()}
        self.assertTrue(any(symbols[n] != compact_symbols[n] for n in symbols if n.startswith("@")))

    def test_owned_ordering_preserves_object_and_rejects_wrong_extent(self):
        layout, error = TB.section_contribution(self.obj, ".data", 0x1000)
        self.assertIsNone(error)
        rows = [{"symbol": name, "address": hex(row["address"]), "size": hex(row["size"])}
                for name, row in layout["symbols"].items() if row["size"]]
        entry = {"module": "ov999", "data": rows, "rodata": [], "bss": [], "functions": []}
        claim = {"name": ".data", "start": 0x1000, "end": 0x1000 + len(layout["bytes"])}
        result, _, errors = TB.prepare_owned_nontext_section_order(self.obj, entry, [claim])
        self.assertEqual(errors, [])
        self.assertEqual(result, self.obj)
        wrong = dict(claim, end=claim["end"] + 1)
        result, _, errors = TB.prepare_owned_nontext_section_order(self.obj, entry, [wrong])
        self.assertIsNone(result)
        self.assertTrue(any("contribution ends" in error for error in errors))
        leading, error = TB.section_contribution(self.obj, ".data", 0x1001)
        self.assertIsNone(error)
        first = min(row["address"] for row in leading["symbols"].values())
        self.assertEqual(leading["bytes"][:first - 0x1001], bytes(first - 0x1001))
        self.assertEqual(first % 4, 0)


if __name__ == "__main__":
    unittest.main()
