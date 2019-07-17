from antlr4 import CommonTokenStream, ParseTreeWalker
from antlr4.FileStream import FileStream
from antlr4.error.ErrorListener import ConsoleErrorListener

from proto_grammar.proto_grammarLexer import proto_grammarLexer
from proto_grammar.proto_grammarParser import proto_grammarParser


# class proto_grammarPrintListener(proto_grammarListener):
#    def enterHi(self, ctx):
#        print("Hello: %s" % ctx.ID())
class MyErrorListener(ConsoleErrorListener):

    def __init__(self):
        super(MyErrorListener, self).__init__()

    def syntaxError(self, recognizer, offendingSymbol, line, column, msg, e):
        super(MyErrorListener, self).syntaxError(recognizer, offendingSymbol, line, column, msg, e)
        raise  Exception()


def main():
    fname = "sv2017.g4_proto"
    f = FileStream(fname, encoding="utf-8")
    lexer = proto_grammarLexer(f)
    stream = CommonTokenStream(lexer)
    parser = proto_grammarParser(stream)
    parser.addErrorListener(MyErrorListener())
    tree = parser.proto_file()
    return tree
    # printer = HelloPrintListener()
    # walker = ParseTreeWalker()
    # walker.walk(printer, tree)


if __name__ == '__main__':
    main()
