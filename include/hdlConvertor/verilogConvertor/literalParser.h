#pragma once

#include <antlr4-runtime.h>
#include <vector>
#include <string>

#include <hdlConvertor/verilogConvertor/Verilog2001Parser/Verilog2001Parser.h>
#include <hdlConvertor/hdlObjects/expr.h>

namespace hdlConvertor {
namespace verilog {

class VerLiteralParser {
public:
	using Expr = hdlObjects::Expr;
	using Verilog2001Parser = Verilog2001_antlr::Verilog2001Parser;
	using TerminalNode = antlr4::tree::TerminalNode;
	typedef hdlObjects::OperatorType OperatorType;

	static Expr * visitNumber(Verilog2001Parser::NumberContext * ctx);
	static Expr * parseSimple_identifier(TerminalNode * n);
	static Expr * parseEscaped_identifier(TerminalNode* n);
	static Expr * parseIntNumber(TerminalNode * n, int radix);
	static Expr * visitString(TerminalNode * n);
	static OperatorType visitUnary_operator(
			Verilog2001Parser::Unary_operatorContext * ctx);
	static OperatorType visitBinary_operator(
			Verilog2001Parser::Binary_operatorContext * ctx);
	static Expr * visitDolar_identifier(TerminalNode* n);
};

}
}
