#include "source_textParser.h"

using namespace Verilog2001;

Source_textParser::Source_textParser(antlr4::TokenStream* tokens, Context * ctx,
		bool _hierarchyOnly) :
		BaseHdlParser(tokens, ctx, _hierarchyOnly) {
}

void Source_textParser::visitSource_text(
		Verilog2001Parser::Source_textContext* ctx) {
	//// START SYMBOL
	// source_text : timing_spec? description* EOF ;
	if (!hierarchyOnly) {
		auto t = ctx->timing_spec();
		if (t)
			visitTiming_spec(t);
	}
	for (auto d : ctx->description()) {
		visitDescription(d);
	}
}
void Source_textParser::visitTiming_spec(
		Verilog2001Parser::Timing_specContext* ctx) {
	// timing_spec : '`timescale' Time_Identifier '/' Time_Identifier;
	NotImplementedLogger::print("Source_textParser.visitTiming_spec");
}
void Source_textParser::visitDescription(
		Verilog2001Parser::DescriptionContext* ctx) {
	// description : module_declaration ;
	ModuleParser * p = new ModuleParser(tokens, context, hierarchyOnly);
	p->visitModule_declaration(ctx->module_declaration());
}
