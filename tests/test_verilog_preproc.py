import os
from os import path
import unittest
import contextlib
from tests.basic_tc import TEST_DIR

from hdlConvertor import ParseException, HdlConvertor
from hdlConvertor.language import Language


@contextlib.contextmanager
def cd(newdir, cleanup=lambda: True):
    prevdir = os.getcwd()
    os.chdir(os.path.expanduser(newdir))

    try:
        yield
    finally:
        os.chdir(prevdir)
        cleanup()


def _test_run(test_file, golden_file):
    c = HdlConvertor()

    incdirs = [path.join('sv_pp', 'src'), ]

    with cd(TEST_DIR):
        # cd to have nice paths in error messages
        test_result = c.verilog_pp(
            test_file, Language.SYSTEM_VERILOG, incdirs)

    # with open(golden_file, "w") as f:
    #     f.write(test_result)

    with open(os.path.join(TEST_DIR, golden_file)) as f:
        test_golden = f.read()

    return test_result, test_golden


def _test_run_rel(test_file, golden_file):
    return _test_run(
            path.join('sv_pp', 'src', test_file),
            path.join('sv_pp', 'expected', golden_file)
    )


class VerilogPreprocTC(unittest.TestCase):

    def assertPPWorks(self, test_file):
        golden_file = test_file  # same name but will get a diffent folder

        result, ref = _test_run_rel(test_file, golden_file)
        # print(result)
        self.assertEqual(result, ref)

    def test_2012_p641(self):
        self.assertPPWorks('2012_p641.txt')

    def test_2012_p642(self):
        self.assertPPWorks('2012_p642.txt')

    def test_2012_p642_2(self):
        self.assertPPWorks('2012_p642_2.txt')

    def test_2012_p643(self):
        self.assertPPWorks('2012_p643.txt')

    def test_2012_p643_2(self):
        self.assertPPWorks('2012_p643_2.txt')

    def test_2012_p643_3(self):
        self.assertPPWorks('2012_p643_3.txt')

    def test_2012_p644(self):
        self.assertPPWorks('2012_p644.txt')

    def assertPPError(self, file, err_msg, contains=False):
        with self.assertRaises(ParseException) as context:
            f = path.join(TEST_DIR, 'sv_pp', 'src', file)
            c = HdlConvertor()
            c.verilog_pp(
                f,
                Language.SYSTEM_VERILOG,
                [path.join('sv_pp', 'src'), ],
            )
        e = str(context.exception)
        if contains:
            self.assertIn(err_msg, e)
        else:
            self.assertGreaterEqual(len(e), len(err_msg))
            _e = e[-len(err_msg):]
            if err_msg != _e:
                # print whole error if there is some problem
                self.assertEqual(err_msg, e)
            else:
                self.assertEqual(err_msg, _e)

    def test_2012_p644_2(self):
        # [TODO] platform dependent path
        self.assertPPError(
            '2012_p644_2.txt',
            "SyntaxError:mismatched input",
            contains=True
        )

    def test_2012_p641_il1(self):
        self.assertPPError(
            '2012_p641_il1.txt',
            'Macro D missing value for parameter y'
            ' (2 arguments expected but 1 provided).'
        )

    def test_2012_p641_il2(self):
        self.assertPPError(
            '2012_p641_il2.txt',
            'Macro D missing value for parameter x and for parameters'
            ' after (2 arguments expected but 0 provided).'
        )

    def test_2012_p641_il3(self):
        self.assertPPError(
            '2012_p641_il3.txt',
            'Macro D expected 2 arguments but 3 provided.'
        )

    def test_2012_p642_il1(self):
        self.assertPPError(
            '2012_p642_il1.txt',
            'Macro MACRO1 missing value for parameter c'
            ' (1 to 3 arguments expected but 1 provided).'
        )

    def test_2012_p642_il2(self):
        self.assertPPError(
            '2012_p642_il2.txt',
            'Macro MACRO3 requires braces and expects 0 to 3 arguments.'
        )

    def test_2012_p642_il3(self):
        self.assertPPError(
            '2012_p642_il3.txt',
            'Unfinished string in definition of macro first_half.'
        )

    def test_FILE_LINE(self):
        c = HdlConvertor()
        f = path.join(path.dirname(__file__), 'sv_pp', 'src', 'test_FILE_LINE.sv')
        incdirs = [path.join('sv_pp', 'src'), ]
        test_result = c.verilog_pp(f, Language.SYSTEM_VERILOG, incdirs)
        expected_val = path.join(path.dirname(__file__),
                                 'sv_pp', 'src', 'test_FILE_LINE.sv'
                                 )
        test_golden = ("module tb();\n\ninitial\n\t$display("
                       "\"Internal error: null handle at %s, line %d.\",\n")
        test_golden += "\"" + expected_val + "\", 5);\n\n\nendmodule\n"
        self.assertEqual(test_result, test_golden)

    def test_verilog_pp_Language_is_bad(self):
        with self.assertRaises(ValueError) as context:
            c = HdlConvertor()
            test_result = c.verilog_pp("", "badlang", [])
        e = str(context.exception)
        self.assertIn("'badlang' is not recognized (expected hdlConvertor.language.Language value)", e)

    def test_parser_Language_is_bad(self):
        with self.assertRaises(ValueError) as context:
            c = HdlConvertor()
            test_result = c.parse(None, "bad", None)
        e = str(context.exception)
        self.assertIn("'bad' is not recognized (expected hdlConvertor.language.Language value)", e)

    def test_debug_macro(self):
        self.assertPPWorks("debug_macro.txt")

    def test_def_in_def(self):
        self.assertPPWorks("def_in_def.txt")

    def test_defined_defargs(self):
        self.assertPPWorks("defined_defargs.txt")

    def test_indirect_ifdef(self):
        self.assertPPError(
            "indirect_ifdef.err.txt",
            "SyntaxError:token recognition error at: '`'",
            contains=True
        )

    def test_preproc_hash_table(self):
        self.assertPPWorks("preproc_hash_table.txt")

    def test_stringify_multiline(self):
        self.assertPPWorks("stringify_multiline.txt")

    def test_stringify(self):
        self.assertPPWorks("stringify.txt")


if __name__ == "__main__":
    suite = unittest.TestSuite()
    # suite.addTest(VerilogPreprocTC('test_stringify_multiline'))
    suite.addTest(unittest.makeSuite(VerilogPreprocTC))

    runner = unittest.TextTestRunner(verbosity=3)
    runner.run(suite)
