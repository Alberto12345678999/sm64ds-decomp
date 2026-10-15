"""Executable regression tests: scanner limits, Git scope, and pinned formatter."""
import contextlib
import io
import json
import os
import pathlib
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import source_style as S

ROOT = pathlib.Path(__file__).resolve().parent.parent
FIXTURES = ROOT / "tools/style_fixtures"
FORMAT = os.environ.get("CLANG_FORMAT") or shutil.which("clang-format")
TIDY = os.environ.get("CLANG_TIDY") or shutil.which("clang-tidy")


class Patterns(unittest.TestCase):
    def test_good_c_and_cpp(self):
        for name in ("good.c", "good.cpp"):
            self.assertEqual([], S.source_findings((FIXTURES / name).read_text()))

    def test_bad_fixture_exercises_every_rule(self):
        found = S.source_findings((FIXTURES / "bad.cpp").read_text())
        self.assertEqual(set(S.RULES), {f.rule for f in found})
        self.assertEqual(2, sum(f.rule == "raw-offset" for f in found))

    def test_comments_and_literals_are_not_findings(self):
        text = '// obj->vtable[3]; _ZN5Actor4TickEv; nullptr\n'
        text += 'const char* s = "unk_74; (int*)(self + 0x74)";\n'
        self.assertEqual([], S.source_findings(text))

    def test_host_bridge_is_not_a_rom_binding(self):
        text = '#ifdef _MSC_VER\nvoid _ZN5Actor4TickEv();\n#else\nvoid Tick();\n#endif\n'
        self.assertEqual([], S.source_findings(text))

    def test_real_mmio_and_callbacks_are_allowed(self):
        text = '*(volatile unsigned*)0x04000208 = 0;\n(*callback)(actor);\n'
        self.assertEqual([], S.source_findings(text))

    def test_old_debt_survives_comment_and_whitespace_edits(self):
        before = '*(int*)(self + 0x74) = 1;\n'
        after = '// explanation\n*(int*) ( self+0x74 ) = 1;\n'
        self.assertEqual([], S.new_findings(before, after))

    def test_new_offset_cannot_replace_an_old_finding(self):
        found = S.new_findings('*(int*)(self + 0x74)=1;', '*(int*)(self + 0x80)=1;')
        self.assertEqual(1, len(found))
        self.assertIn('0x80', found[0].match)

    def test_duplicate_occurrence_is_a_regression(self):
        text = '_ZN5Actor4TickEv(actor);\n'
        self.assertEqual(1, len(S.new_findings(text, text + text)))

    def test_deletion_does_not_add_debt(self):
        self.assertEqual([], S.new_findings('p->vtable[3](p);', 'Tick();'))

    def test_line_numbers_survive_masking(self):
        text = '/*\nnullptr\n*/\nvoid f() { nullptr; }\n'
        self.assertEqual(4, S.source_findings(text)[0].line)

    def test_line_endings_are_not_source_changes(self):
        self.assertEqual([], S.added_ranges('int x;\r\n', 'int x;\n'))

    def test_changed_ranges_ignore_deletion_only(self):
        self.assertEqual([], S.added_ranges('a\nb\n', 'a\n'))
        self.assertEqual([(2, 2)], S.added_ranges('a\nb\n', 'a\nc\n'))


class Exceptions(unittest.TestCase):
    def row(self, **changes):
        row = dict(path='src/a.cpp', rule='handspelled-member', match='_ZN1A1fEv',
                   count=1, reason='Measured destructor ABI bridge', evidence='issue/123#experiment')
        row.update(changes)
        return row

    def load(self, rows):
        with tempfile.TemporaryDirectory() as td:
            p = pathlib.Path(td) / 'exceptions.json'
            p.write_text(json.dumps(dict(schema=1, exceptions=rows)))
            return S.load_exceptions(p)

    def test_exception_is_exact_and_counted(self):
        budget = self.load([self.row()])
        findings = S.source_findings('_ZN1A1fEv(); _ZN1A1fEv(); _ZN1B1fEv();')
        self.assertEqual(2, len(S.apply_exceptions('src/a.cpp', findings, budget)))
        self.assertEqual(3, len(S.apply_exceptions('src/b.cpp', findings, budget)))

    def test_exception_is_a_total_cap_across_successive_baselines(self):
        budget = self.load([self.row()])
        one = '_ZN1A1fEv();\n'
        first = S.apply_exceptions('src/a.cpp', S.new_findings('', one), budget, '')
        second = S.apply_exceptions('src/a.cpp', S.new_findings(one, one + one), budget, one)
        third = S.apply_exceptions('src/a.cpp', S.new_findings(one + one, one * 3), budget, one + one)
        self.assertEqual([], first)
        self.assertEqual(1, len(second))
        self.assertEqual(1, len(third))

    def test_empty_reason_evidence_and_wildcards_fail(self):
        for changes in ({'reason': ''}, {'evidence': ''}, {'rule': '*'}, {'path': '../a.cpp'},
                        {'path': 'src/*.cpp'}, {'count': 0}, {'count': True}):
            with self.subTest(changes=changes), self.assertRaises(S.StyleError):
                self.load([self.row(**changes)])

    def test_duplicate_and_unknown_keys_fail(self):
        with self.assertRaises(S.StyleError):
            self.load([self.row(), self.row()])
        with self.assertRaises(S.StyleError):
            self.load([self.row(extra='not supported')])

    def test_missing_config_does_not_skip(self):
        with self.assertRaises(S.StyleError):
            S.load_exceptions(ROOT / 'build/definitely-missing-style-exceptions.json')


class GitScope(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = pathlib.Path(self.temp.name)
        self.run_git('init', '-q')
        self.run_git('config', 'user.name', 'Style Test')
        self.run_git('config', 'user.email', 'style-test@example.invalid')
        self.run_git('config', 'core.autocrlf', 'false')
        (self.root / 'src').mkdir()
        (self.root / 'config').mkdir()
        (self.root / 'config/source-style-exceptions.json').write_text('{"schema":1,"exceptions":[]}')
        (self.root / 'src/old.cpp').write_text('//cpp\nvoid f(){_ZN1A1fEv();}\n')
        self.run_git('add', '.')
        self.run_git('commit', '-qm', 'base')
        self.base = self.run_git('rev-parse', 'HEAD').strip()

    def run_git(self, *args):
        return subprocess.check_output(['git', '-C', str(self.root), *args], text=True)

    def check(self, base=None):
        return S.check(self.root, base or self.base, None, None, patterns_only=True)

    def test_staged_unstaged_and_untracked_inputs(self):
        (self.root / 'src/old.cpp').write_text('//cpp\nvoid f(){_ZN1A1fEv(); _ZN1B1fEv();}\n')
        self.run_git('add', 'src/old.cpp')
        (self.root / 'src/new.c').write_text('void f(){nullptr;}\n')
        report = self.check()
        self.assertEqual(2, report['files_checked'])
        self.assertEqual(2, len(report['findings']))
        (self.root / 'src/old.cpp').write_text('//cpp\nvoid f(){_ZN1A1fEv(); _ZN1C1fEv();}\n')
        self.assertTrue(any(f['match'] == '_ZN1C1fEv' for f in self.check()['findings']))

    def test_rename_keeps_debt_but_new_copy_does_not(self):
        self.run_git('mv', 'src/old.cpp', 'src/renamed.cpp')
        self.assertEqual([], self.check()['findings'])
        for path in ('src/renamed.cpp', str(self.root / 'src/renamed.cpp')):
            report = S.check(self.root, self.base, [path], None, patterns_only=True)
            self.assertEqual([], report['findings'])
        shutil.copyfile(self.root / 'src/renamed.cpp', self.root / 'src/copied.cpp')
        self.assertEqual(1, len(self.check()['findings']))

    def test_baselined_occurrence_consumes_exception_cap(self):
        row = dict(path='src/old.cpp', rule='handspelled-member', match='_ZN1A1fEv',
                   count=1, reason='Measured ABI bridge', evidence='issue/123#experiment')
        (self.root / 'config/source-style-exceptions.json').write_text(
            json.dumps(dict(schema=1, exceptions=[row])))
        (self.root / 'src/old.cpp').write_text('//cpp\nvoid f(){_ZN1A1fEv(); _ZN1A1fEv();}\n')
        self.assertEqual(1, len(self.check()['findings']))

    def test_deleted_file_is_not_opened(self):
        self.run_git('rm', '-q', 'src/old.cpp')
        self.assertEqual(0, self.check()['files_checked'])

    def test_bad_base_is_fatal(self):
        with self.assertRaises(S.StyleError):
            self.check('missing-base-ref')

    def test_merge_base_excludes_changes_on_the_other_branch(self):
        self.run_git('branch', 'pr-base')
        self.run_git('checkout', '-qb', 'other')
        (self.root / 'src/other.cpp').write_text('void f(){nullptr;}\n')
        self.run_git('add', '.')
        self.run_git('commit', '-qm', 'other branch')
        self.run_git('branch', '-f', 'pr-base', 'HEAD')
        self.run_git('checkout', '-q', '--detach', self.base)
        self.assertEqual(0, self.check('pr-base')['files_checked'])

    def test_explicit_missing_file_and_path_escape_are_errors(self):
        for path in ('src/missing.cpp', '../escape.cpp'):
            with self.subTest(path=path), self.assertRaises((OSError, S.StyleError)):
                S.check(self.root, None, [path], None, patterns_only=True)

    def test_formatter_required_even_with_zero_inputs(self):
        with self.assertRaises(S.StyleError):
            S.check(self.root, self.base, None, None)


class Formatter(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not FORMAT:
            raise RuntimeError('Install tools/requirements-style.txt; formatter fixtures cannot be skipped')
        S.formatter_version(FORMAT)

    def test_exact_fixture_and_idempotence(self):
        raw = (FIXTURES / 'format-input.cpp').read_bytes()
        expected = (FIXTURES / 'format-expected.cpp').read_bytes().replace(b'\r\n', b'\n')
        def fmt(text):
            return subprocess.check_output([FORMAT, f'--style=file:{ROOT / ".clang-format"}',
                                            '--assume-filename=fixture.cpp'], input=text).replace(b'\r\n', b'\n')
        self.assertEqual(expected, fmt(raw))
        self.assertEqual(expected, fmt(expected))
        self.assertTrue(expected.startswith(b'//cpp\n'))
        self.assertLess(expected.index(b'z_fixture.h'), expected.index(b'a_fixture.h'))

    def test_good_files_are_formatted(self):
        for name in ('good.cpp', 'good.c', 'format-expected.cpp'):
            text = (FIXTURES / name).read_text()
            self.assertEqual([], S.format_findings(FORMAT, ROOT / '.clang-format', name,
                                                   text, [(1, len(text.splitlines()))]))

    def test_new_bad_formatting_is_reported(self):
        text = 'void f(){return;}\n'
        self.assertTrue(S.format_findings(FORMAT, ROOT / '.clang-format', 'a.cpp', text, [(1, 1)]))

    def test_new_line_indentation_uses_preceding_newline_replacement(self):
        for before, after, line in (
                ('void f()\n{\n}\n', 'void f()\n{\nx();\n}\n', 3),
                ('void f()\n{\n    x();\n}\n', 'void f()\n{\n    x();\ny();\n}\n', 4)):
            findings = S.format_findings(FORMAT, ROOT / '.clang-format', 'a.cpp', after,
                                        S.added_ranges(before, after))
            self.assertTrue(findings)
            self.assertTrue(any(f.line == line for f in findings))

    def test_old_unformatted_line_is_not_a_new_error(self):
        before = 'void old(){return;}\n\nint x;\n'
        after = before + 'int y;\n'
        self.assertEqual([], S.format_findings(FORMAT, ROOT / '.clang-format', 'a.cpp', after,
                                               S.added_ranges(before, after)))

    def test_utf8_offsets_are_bytes(self):
        text = '// Unicode: \u00e9\nvoid f(){return;}\n'
        findings = S.format_findings(FORMAT, ROOT / '.clang-format', 'a.cpp', text, [(2, 2)])
        self.assertTrue(findings)
        self.assertTrue(all(f.line == 2 for f in findings))

    def test_wrong_version_is_fatal(self):
        for version in ('18.1.0', '19.1.7.1'):
            result = subprocess.CompletedProcess([], 0, stdout='clang-format version ' + version)
            with self.subTest(version=version), patch.object(S.subprocess, 'run', return_value=result):
                with self.assertRaises(S.StyleError):
                    S.formatter_version('formatter')

    def test_invalid_xml_and_incomplete_formatting_are_fatal(self):
        for data in (b'invalid', b'<replacements incomplete_format="true"/>'):
            result = subprocess.CompletedProcess([], 0, stdout=data, stderr=b'')
            with self.subTest(data=data), patch.object(S.subprocess, 'run', return_value=result):
                with self.assertRaises(S.StyleError):
                    S.format_findings('formatter', ROOT / '.clang-format', 'a.cpp', 'int x;', [(1, 1)])

    def test_requirements_and_checker_pins_agree(self):
        self.assertIn('clang-format==' + S.FORMAT_VERSION,
                      (ROOT / 'tools/requirements-style.txt').read_text().splitlines())


class AdvisoryTidy(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not TIDY:
            raise RuntimeError('Install tools/requirements-style.txt; advisory config fixtures cannot be skipped')

    def test_only_explicit_checks_enabled(self):
        p = subprocess.run([TIDY, '--list-checks', '--config-file=' + str(ROOT / '.clang-tidy')],
                           capture_output=True, text=True)
        self.assertEqual(0, p.returncode, p.stderr)
        checks = {line.strip() for line in p.stdout.splitlines() if line.strip().startswith(('bugprone-', 'modernize-', 'clang-analyzer-'))}
        self.assertEqual({'bugprone-sizeof-expression', 'bugprone-suspicious-memset-usage'}, checks)

    def test_clean_cpp03_arm_fixture_parses(self):
        p = subprocess.run([TIDY, str(FIXTURES / 'good.cpp'),
                            '--config-file=' + str(ROOT / '.clang-tidy'), '--',
                            '-x', 'c++', '-std=c++03', '-target', 'arm-none-eabi', '-mcpu=arm946e-s'],
                           capture_output=True, text=True)
        self.assertEqual(0, p.returncode, p.stdout + p.stderr)
        self.assertNotIn('warning:', p.stdout + p.stderr)


class CommandLine(unittest.TestCase):
    def test_bad_fixture_returns_nonzero_and_records_scope(self):
        with contextlib.redirect_stdout(io.StringIO()) as output:
            code = S.main(['--files', 'tools/style_fixtures/bad.cpp', '--patterns-only'])
        self.assertEqual(1, code)
        self.assertIn('PATTERNS ONLY', output.getvalue())
        self.assertIn('6 finding(s)', output.getvalue())


if __name__ == '__main__':
    unittest.main()
