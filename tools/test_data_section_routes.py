"""Native initialized slices retain exact ELF identities and ordinary byte gates."""
import copy
import io
import pathlib
import struct
import sys
import tempfile
import unittest

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import data_section_routes as DSR
import tubuild as TB


class RouteSchema(unittest.TestCase):
    def test_names_are_initialized_only_and_require_explicit_origin(self):
        self.assertEqual(DSR.initialized_kind('.data.clps0'), '.data')
        for name in ('.bss.node', '.text.body', '.data_gap', '.data../escape'):
            self.assertIsNone(DSR.initialized_kind(name))
        for row in ({'name': '.data.a'},
                    {'name': '.data.a', 'input_section': '.rodata'},
                    {'name': '.bss.a', 'input_section': '.bss'}):
            self.assertTrue(DSR.routes({'sections': [row]})[1])
        self.assertTrue(DSR.routes({'sections': None})[1])

    def test_control_fingerprint_includes_routing_code(self):
        self.assertIn(pathlib.Path(DSR.__file__).resolve(),
                      [p.resolve() for p in TB.BASELINE_CONTROL_TOOLS])

    def test_malformed_names_refuse_without_unhashable_exceptions(self):
        for value in ([], {}, None, 1):
            self.assertIsNone(DSR.initialized_kind(value))
            for field in ('name', 'module_section'):
                row = {'name': '.data', 'start': '0x2000', 'end': '0x2004'}
                row[field] = value
                entry = {'sections': [row]}
                self.assertTrue(TB.manifest_section_claims(entry)[1])
                entry.update(id='malformed', production_mode='intact-object',
                             promoted_source='src/actors/Test.cpp', status='promoted')
                with self.assertRaises(TB.RB.BuildError):
                    TB.RB.intact_tu_policies(manifest={'entries': [entry]})
        entry['sections'] = None
        with self.assertRaises(TB.RB.BuildError):
            TB.RB.intact_tu_policies(manifest={'entries': [entry]})


class NativeRoutes(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not (TB.RB.MW / '2004/b56/mwccarm.exe').is_file():
            raise unittest.SkipTest('private pinned compiler unavailable')
        cls.directory = tempfile.TemporaryDirectory(prefix='data-routes-', dir=TB.REPO / 'build')
        source = pathlib.Path(cls.directory.name) / 'fixture.cpp'
        source.write_text('extern "C" int target;\n'
                          'extern "C" int words[2] = {11, 22};\n'
                          'extern "C" int *pointer = &target;\n'
                          'extern "C" int ordinary = 33;\n')
        cls.raw = TB.M.compile_c(source, '2004/b56', TB.RB.CFLAGS.replace('-lang c99', '-lang c++'))
        if cls.raw is None:
            raise AssertionError('native fixture did not compile')
        cls.entry = {'module': 'ov999', 'sections': [
            {'name': '.text', 'start': '0x1000', 'end': '0x1004'},
            {'name': '.data.words', 'input_section': '.data', 'start': '0x2000', 'end': '0x2008'},
            {'name': '.data.pointer', 'input_section': '.data', 'start': '0x2020', 'end': '0x2024'},
            {'name': '.data', 'start': '0x2040', 'end': '0x2044'}],
            'data': [{'symbol': 'words', 'address': '0x2000', 'size': 8},
                     {'symbol': 'pointer', 'address': '0x2020', 'size': 4},
                     {'symbol': 'ordinary', 'address': '0x2040', 'size': 4}],
            'relocations': [{'section': '.data.pointer', 'source': '0x2020',
                             'type': 'R_ARM_ABS32', 'kind': 'load', 'symbol': 'target',
                             'addend': 0, 'target_module': 'arm9', 'target_address': '0x9000'}]}

    @classmethod
    def tearDownClass(cls):
        cls.directory.cleanup()

    def route(self, entry=None):
        entry = entry or self.entry
        claims, errors = TB.manifest_section_claims(entry)
        self.assertFalse(errors, errors)
        routed, report, errors = TB.prepare_owned_nontext_section_order(self.raw, entry, claims)
        self.assertFalse(errors, errors)
        return routed, report, claims

    def test_whole_native_sections_keep_all_symbol_and_relocation_indices(self):
        routed, report, _ = self.route()
        old, new = ELFFile(io.BytesIO(self.raw)), ELFFile(io.BytesIO(routed))
        self.assertEqual(old.num_sections(), new.num_sections())
        self.assertEqual(old.get_section_by_name('.symtab').data(),
                         new.get_section_by_name('.symtab').data())
        changed = {r['sectionIndex']: r['to'] for r in report['routing']['routes']}
        for i, (before, after) in enumerate(zip(old.iter_sections(), new.iter_sections())):
            self.assertEqual(after.name, changed.get(i, before.name))
            if i != old['e_shstrndx']:
                self.assertEqual(before.data(), after.data())
                for key in ('sh_size', 'sh_type', 'sh_link', 'sh_info', 'sh_addralign', 'sh_flags'):
                    self.assertEqual(before[key], after[key])
        repeated, _, errors = DSR.apply(routed, self.entry)
        self.assertFalse(errors)
        self.assertEqual(routed, repeated)

    def test_wrong_object_size_provider_and_partial_section_are_refused(self):
        for change in ('wrong_symbol', 'wrong_size', 'partial_section', 'wrong_native_section'):
            entry = copy.deepcopy(self.entry)
            if change == 'wrong_symbol':
                entry['data'][0]['symbol'] = 'absent'
            elif change == 'wrong_size':
                entry['data'][0]['size'] = 4
            elif change == 'partial_section':
                entry['data'][0]['address'] = '0x2004'
                entry['sections'][1]['end'] = '0x200c'
                entry['sections'][1]['start'] = '0x2004'
                # An object beginning inside its section cannot masquerade as its prefix.
                raw = bytearray(self.raw)
                elf = ELFFile(io.BytesIO(raw)); st = elf.get_section_by_name('.symtab')
                i = next(i for i, s in enumerate(st.iter_symbols()) if s.name == 'words')
                struct.pack_into('<I', raw, st['sh_offset'] + i * st['sh_entsize'] + 4, 4)
                self.assertTrue(DSR.apply(bytes(raw), entry)[2]); continue
            else:
                entry['sections'][1]['name'] = '.rodata.words'
                entry['sections'][1]['input_section'] = '.rodata'
                entry['rodata'] = [entry['data'].pop(0)]
            self.assertTrue(DSR.apply(self.raw, entry)[2], change)

    def test_overlapping_routes_are_refused(self):
        entry = copy.deepcopy(self.entry)
        entry['sections'][2].update(start='0x2004', end='0x2008')
        self.assertTrue(DSR.apply(self.raw, entry)[2])

    def test_unlicensed_occupant_in_routed_native_section_is_refused(self):
        raw = bytearray(self.raw)
        elf = ELFFile(io.BytesIO(raw)); st = elf.get_section_by_name('.symtab')
        syms = list(st.iter_symbols())
        words = next(s for s in syms if s.name == 'words')
        index = next(i for i, s in enumerate(syms) if s.name == 'ordinary')
        offset = st['sh_offset'] + index * st['sh_entsize']
        struct.pack_into('<H', raw, offset + 14, words['st_shndx'])
        self.assertTrue(any('unlicensed occupants' in e
                            for e in DSR.apply(bytes(raw), self.entry)[2]))

    def test_duplicate_owned_anchor_is_refused(self):
        entry = copy.deepcopy(self.entry)
        entry['data'].append(dict(entry['data'][0]))
        self.assertTrue(DSR.apply(self.raw, entry)[2])

    def audit(self, raw, entry=None, destination=0x9000, reader=None):
        entry = entry or self.entry
        claims, errors = TB.manifest_section_claims(entry)
        self.assertFalse(errors)
        payload = {0x2000: struct.pack('<2I', 11, 22),
                   0x2020: struct.pack('<I', 0x9000), 0x2040: struct.pack('<I', 33)}
        return TB.verify_owned_sections(raw, entry, claims,
            name_index={'target': ('arm9', destination)},
            config_relocs={'ov999': {0x2020: ('load', 0x9000, 'arm9')}},
            sym_index={}, symbol_homes={}, bss_boundaries=set(),
            target_reader=reader or (lambda module, address, size: payload[address]))

    def test_routing_retains_wrong_destination_and_changed_bytes_rejection(self):
        routed, _, _ = self.route()
        good = self.audit(routed)
        self.assertTrue(good['ok'], good.get('errors'))
        wrong = self.audit(routed, destination=0x9004)
        self.assertFalse(wrong['ok'])
        damaged = bytearray(routed); elf = ELFFile(io.BytesIO(routed))
        section = elf.get_section_by_name('.data.words'); damaged[section['sh_offset']] ^= 1
        self.assertFalse(self.audit(bytes(damaged))['ok'])
        damaged = bytearray(routed)
        rel = next(s for s in elf.iter_sections() if s['sh_type'] == 'SHT_RELA')
        struct.pack_into('<i', damaged, rel['sh_offset'] + 8, 4)
        self.assertFalse(self.audit(bytes(damaged))['ok'])


if __name__ == '__main__':
    unittest.main()
