#include <hdlConvertor/svConvertor/moduleParser.h>

#include <hdlConvertor/notImplementedLogger.h>
#include <hdlConvertor/conversion_exception.h>

#include <hdlConvertor/svConvertor/utils.h>
#include <hdlConvertor/svConvertor/portParser.h>
#include <hdlConvertor/svConvertor/exprParser.h>
#include <hdlConvertor/svConvertor/statementParser.h>
#include <hdlConvertor/svConvertor/moduleInstanceParser.h>
#include <hdlConvertor/svConvertor/paramDefParser.h>
#include <hdlConvertor/svConvertor/attributeParser.h>
#include <hdlConvertor/svConvertor/portParser.h>
#include <hdlConvertor/svConvertor/typeParser.h>
#include <hdlConvertor/svConvertor/declrParser.h>
#include <hdlConvertor/svConvertor/programParser.h>


namespace hdlConvertor {
namespace sv {

using namespace std;
using namespace sv2017_antlr;
using namespace hdlConvertor::hdlObjects;

VerModuleParser::VerModuleParser(SVCommentParser &commentParser,
		bool _hierarchyOnly) :
		commentParser(commentParser) {
	hierarchyOnly = _hierarchyOnly;
	ent = nullptr;
	arch = nullptr;
}
void VerModuleParser::visitModule_header_common(
		sv2017Parser::Module_header_commonContext *ctx) {
	// module_header_common:
	//   ( attribute_instance )* module_keyword ( lifetime )? identifier
	//   ( package_import_declaration )* ( parameter_port_list )?;
	VerAttributeParser::visitAttribute_instance(ctx->attribute_instance());
	auto lt = ctx->lifetime();
	if (lt) {
		NotImplementedLogger::print(
				"VerModuleParser.visitModule_header_common - lifetime", lt);
	}
	ent->__doc__ = commentParser.parse(ctx);
	ent->name = ctx->identifier()->getText();
	for (auto pid : ctx->package_import_declaration()) {
		NotImplementedLogger::print(
				"VerModuleParser.visitModule_header_common - package_import_declaration",
				pid);
	}
	auto mppl = ctx->parameter_port_list();
	if (mppl) {
		VerParamDefParser pp(commentParser);
		pp.visitParameter_port_list(mppl, ent->generics);
	}
}
void VerModuleParser::visitModule_declaration(
		sv2017Parser::Module_declarationContext *ctx,
		std::vector<iHdlObj*> &res) {
	// module_declaration:
	//   KW_EXTERN module_header_common ( list_of_port_declarations )? SEMI
	//    | module_header_common (list_of_port_declarations | (LPAREN DOT MUL RPAREN) )? SEMI
	//        ( timeunits_declaration )? ( module_item )*
	//      KW_ENDMODULE ( COLON identifier | {_input->LA(1) != COLON}? )
	// ;

	// module_declaration
	// : attribute_instance* module_keyword module_identifier
	// ( module_parameter_port_list )? ( list_of_ports )? ';' module_item*
	// 'endmodule'
	// | attribute_instance* module_keyword module_identifier
	// ( module_parameter_port_list )? ( list_of_port_declarations )? ';'
	// non_port_module_item*
	// 'endmodule'
	// ;
	auto mhc = ctx->module_header_common();
	assert(ent == nullptr);
	ent = new HdlModuleDec();

	visitModule_header_common(mhc);

	auto lpd = ctx->list_of_port_declarations();
	if (lpd) {
		VerPortParser pp(commentParser, non_ANSI_port_groups);
		auto ps = pp.visitList_of_port_declarations(lpd);
		for (auto p : *ps) {
			ent->ports.push_back(p);
		}
		delete ps;
	}
	res.push_back(ent);
	if (ctx->KW_EXTERN()) {
		ent = nullptr;
		return;
	}

	arch = new HdlModuleDef();
	auto tid = ctx->timeunits_declaration();
	if (tid) {
		NotImplementedLogger::print(
				"ModuleParser.visitModule_declaration.timeunits_declaration",
				tid);
	}
	for (auto mi : ctx->module_item())
		visitModule_item(mi, arch->objs);

	arch->entityName = iHdlExpr::ID(ent->name);
	res.push_back(arch);
	if (non_ANSI_port_groups.size()) {
		VerPortParser pp(commentParser, non_ANSI_port_groups);
		pp.convert_non_ansi_ports_to_ansi(ent->ports, arch->objs);
	}
	for (auto o : ent->ports) {
		if (o->type == nullptr) {
			throw ParseException(
					string("Can not find type specification for port ")
							+ ent->name + "::" + o->name);
		}
	}
	ent = nullptr;
	arch = nullptr;
}
void VerModuleParser::visitModule_item_item(
		sv2017Parser::Module_item_itemContext *ctx, vector<iHdlObj*> &res) {
	// module_item_item:
	//     parameter_override
	//     | gate_instantiation
	//     | udp_instantiation
	//     | module_or_interface_or_program_instantiation
	//     | ( default_clocking_or_dissable_construct
	//         | local_parameter_declaration
	//         | parameter_declaration )? SEMI
	//     | net_declaration
	//     | data_declaration
	//     | task_declaration
	//     | function_declaration
	//     | checker_declaration
	//     | dpi_import_export
	//     | extern_constraint_declaration
	//     | class_declaration
	//     | interface_class_declaration
	//     | class_constructor_declaration
	//     | covergroup_declaration
	//     | property_declaration
	//     | sequence_declaration
	//     | let_declaration
	//     | genvar_declaration
	//     | clocking_declaration
	//     | assertion_item
	//     | bind_directive
	//     | continuous_assign
	//     | net_alias
	//     | initial_construct
	//     | final_construct
	//     | always_construct
	//     | loop_generate_construct
	//     | conditional_generate_construct
	//     | elaboration_system_task
	//     | specparam_declaration
	// ;
	auto &res_stm = *reinterpret_cast<vector<iHdlStatement*>*>(&res);
	auto &res_vars = *reinterpret_cast<vector<HdlVariableDef*>*>(&res);
	{
		auto o = ctx->parameter_override();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.parameter_override",
					o);
			return;
		}
	}
	{
		auto o = ctx->gate_instantiation();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.gate_instantiation",
					o);
			return;
		}
	}
	{
		auto o = ctx->udp_instantiation();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.udp_instantiation",
					o);
			return;
		}
	}
	{
		auto o = ctx->module_or_interface_or_program_instantiation();
		if (o) {

			auto &res_comp = *reinterpret_cast<vector<HdlCompInstance*>*>(&res);
			VerModuleInstanceParser mp(commentParser);
			mp.visitModule_or_interface_or_program_instantiation(o, res_comp);
			return;
		}
	}
	{
		auto o = ctx->default_clocking_or_dissable_construct();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.default_clocking_or_dissable_construct",
					o);
			return;
		}
	}
	{
		auto o = ctx->local_parameter_declaration();
		if (o) {
			VerParamDefParser pdp(commentParser);
			pdp.visitLocal_parameter_declaration(o, res_vars);
		}
	}
	{
		auto o = ctx->parameter_declaration();
		if (o) {
			VerParamDefParser pdp(commentParser);
			pdp.visitParameter_declaration(o, res_vars);
			return;
		}
	}
	{
		if (ctx->SEMI()) {
			res_stm.push_back(iHdlStatement::NOP());
			return;
		}
	}
	{
		auto o = ctx->net_declaration();
		if (o) {
			visitNet_declaration(o, res_vars);
			return;
		}
	}
	{
		auto o = ctx->data_declaration();
		if (o) {
			return VerDeclrParser(commentParser).visitData_declaration(o, res);
		}
	}
	{
		auto o = ctx->task_declaration();
		if (o) {
			VerProgramParser pp(commentParser);
			auto f = pp.visitTask_declaration(o);
			res.push_back(f);
			return;
		}
	}
	{
		auto o = ctx->function_declaration();
		if (o) {
			VerProgramParser pp(commentParser);
			auto f = pp.visitFunction_declaration(o);
			res.push_back(f);
			return;
		}
	}
	{
		auto o = ctx->checker_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.checker_declaration",
					o);
			return;
		}
	}
	{
		auto o = ctx->dpi_import_export();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.dpi_import_export",
					o);
			return;
		}
	}
	{
		auto o = ctx->extern_constraint_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.extern_constraint_declaration",
					o);
			return;
		}
	}
	{
		auto o = ctx->class_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.class_declaration",
					o);
			return;
		}
	}
	{
		auto o = ctx->interface_class_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.interface_class_declaration",
					o);
			return;
		}
	}
	{
		auto o = ctx->class_constructor_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.class_constructor_declaration",
					o);
			return;
		}
	}
	{
		auto o = ctx->covergroup_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.covergroup_declaration",
					o);
			return;
		}
	}
	{
		auto o = ctx->property_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.property_declaration",
					o);
			return;
		}
	}
	{
		auto o = ctx->sequence_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.sequence_declaration",
					o);
			return;
		}
	}
	{
		auto o = ctx->let_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.let_declaration", o);
			return;
		}
	}
	{
		auto o = ctx->genvar_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.genvar_declaration",
					o);
			return;
		}
	}
	{
		auto o = ctx->clocking_declaration();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.clocking_declaration",
					o);
			return;
		}
	}
	{
		auto o = ctx->assertion_item();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.assertion_item", o);
			return;
		}
	}
	{
		auto o = ctx->bind_directive();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.bind_directive", o);
			return;
		}
	}
	{
		auto o = ctx->continuous_assign();
		if (o) {
			VerStatementParser sp(commentParser);
			sp.visitContinuous_assign(o, res_stm);
			return;
		}
	}
	{
		auto o = ctx->net_alias();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.net_alias", o);
			return;
		}
	}
	{
		auto o = ctx->initial_construct();
		if (o) {
			VerStatementParser sp(commentParser);
			auto ic = sp.visitInitial_construct(o);
			res.push_back(ic);
			return;
		}
	}
	{
		auto o = ctx->final_construct();
		if (o) {
			//VerStatementParser sp(commentParser);
			//auto fc =  sp.visitFinal_construct(o);
			//res.push_back(fc);
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.final_construct", o);
			return;
		}
	}
	{
		auto o = ctx->always_construct();
		if (o) {
			VerStatementParser sp(commentParser);
			auto ac = sp.visitAlways_construct(o);
			res.push_back(ac);
			return;
		}
	}
	{
		auto o = ctx->loop_generate_construct();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.loop_generate_construct",
					o);
			return;
		}
	}
	{
		auto o = ctx->conditional_generate_construct();
		if (o) {
			NotImplementedLogger::print(
					"VerModuleParser.visitModule_item_item.conditional_generate_construct",
					o);
			return;
		}
	}
	{
		auto o = ctx->elaboration_system_task();
		if (o) {
			VerStatementParser sp(commentParser);
			auto est = sp.visitElaboration_system_task(o);
			res.push_back(est);
			return;
		}
	}
	{
		auto o = ctx->specparam_declaration();
		assert(o);
		NotImplementedLogger::print(
				"VerModuleParser.visitModule_item_item.specparam_declaration",
				o);
	}

}
void VerModuleParser::visitModule_item(sv2017Parser::Module_itemContext *ctx,
		std::vector<hdlObjects::iHdlObj*> &objs) {
	// module_item:
	//     generate_region
	//     | ( attribute_instance )* module_item_item
	//     | specify_block
	//     | program_declaration
	//     | module_declaration
	//     | interface_declaration
	//     | timeunits_declaration
	//     | nonansi_port_declaration SEMI
	// ;
	auto gr = ctx->generate_region();
	if (gr) {
		NotImplementedLogger::print("ModuleParser.module_item.generate_region",
				gr);
		return;
	}
	auto mii = ctx->module_item_item();
	if (mii) {
		auto ai = ctx->attribute_instance();
		VerAttributeParser::visitAttribute_instance(ai);
		visitModule_item_item(mii, objs);
		return;
	}
	auto sb = ctx->specify_block();
	if (sb) {
		NotImplementedLogger::print("ModuleParser.module_item.specify_block",
				sb);
		return;
	}
	auto pd = ctx->program_declaration();
	if (pd) {
		NotImplementedLogger::print(
				"ModuleParser.module_item.program_declaration", pd);
		return;
	}
	auto md = ctx->module_declaration();
	if (md) {
		VerModuleParser mp(commentParser, hierarchyOnly);
		mp.visitModule_declaration(md, objs);
		return;
	}
	auto id = ctx->interface_declaration();
	if (id) {
		NotImplementedLogger::print(
				"ModuleParser.module_item.interface_declaration", pd);
		return;
	}
	auto td = ctx->timeunits_declaration();
	if (td) {
		NotImplementedLogger::print(
				"ModuleParser.module_item.timeunits_declaration", td);
		return;
	}
	auto npd = ctx->nonansi_port_declaration();
	if (npd) {
		// update port in module header to an ansi port
		string doc = commentParser.parse(ctx);
		bool first = true;
		VerPortParser pp(commentParser, non_ANSI_port_groups);
		std::vector<HdlVariableDef*> portsDeclr;
		pp.visitNonansi_port_declaration(npd, portsDeclr);
		for (auto declr : portsDeclr) {
			HdlVariableDef *p = ent->getPortByName(declr->name);
			p->direction = declr->direction;
			assert(p != nullptr);
			p->type = declr->type;
			if (declr->value) {
				assert(p->value == nullptr);
				p->value = declr->value;
			}
			p->is_latched |= declr->is_latched;
			p->is_const |= declr->is_const;
			if (p->direction == HdlDirection::DIR_UNKNOWN)
				p->direction = declr->direction;
			if (first) {
				p->__doc__ += doc;
				first = false;
			}
			delete declr;
		}
		return;
	}

	throw std::runtime_error(
			"ModuleParser.visitModule_item - probably missing part of implementation");
}

void VerModuleParser::visitNet_declaration(
		sv2017Parser::Net_declarationContext *ctx,
		vector<HdlVariableDef*> &res) {
	// net_declaration:
	//  ( KW_INTERCONNECT ( implicit_data_type )? ( HASH delay_value )? identifier ( unpacked_dimension )* (
	//   COMMA identifier ( unpacked_dimension )* )?
	//   | ( net_type ( drive_strength
	//                   | charge_strength
	//                   )? ( KW_VECTORED
	//                           | KW_SCALARED
	//                           )? ( data_type_or_implicit )? ( delay3 )?
	//       | identifier ( delay_control )?
	//       ) list_of_net_decl_assignments
	//   ) SEMI;
	if (ctx->KW_INTERCONNECT()) {
		NotImplementedLogger::print(
				"ModuleParser.visitNet_declaration.net_type interconnect", ctx);
		return;
	}
	VerTypeParser tp(commentParser);
	iHdlExpr *net_type = nullptr;
	auto nt = ctx->net_type();
	if (nt) {
		net_type = tp.visitNet_type(nt);
	}
	if (ctx->drive_strength()) {
		NotImplementedLogger::print(
				"ModuleParser.visitNet_declaration.net_type drive_strength",
				ctx);
		return;
	}
	if (ctx->charge_strength()) {
		NotImplementedLogger::print(
				"ModuleParser.visitNet_declaration.net_type charge_strength",
				ctx);
		return;
	}
	if (ctx->KW_VECTORED()) {
		NotImplementedLogger::print(
				"ModuleParser.visitNet_declaration.net_type KW_VECTORED", ctx);
		return;
	}
	if (ctx->KW_SCALARED()) {
		NotImplementedLogger::print(
				"ModuleParser.visitNet_declaration.net_type KW_SCALARED", ctx);
		return;
	}

	auto del = ctx->delay3();
	if (del) {
		NotImplementedLogger::print("ModuleParser.visitNet_declaration.delay3",
				del);
	}
	auto ds = ctx->drive_strength();
	if (ds) {
		NotImplementedLogger::print(
				"ModuleParser.visitNet_declaration.drive_strength", ds);
	}
	auto cs = ctx->charge_strength();
	if (cs) {
		NotImplementedLogger::print(
				"ModuleParser.visitNet_declaration.charge_strength", cs);
	}

	auto dti = ctx->data_type_or_implicit();
	iHdlExpr *t = tp.visitData_type_or_implicit(dti, net_type);
	auto doc = commentParser.parse(ctx);
	auto lna = ctx->list_of_net_decl_assignments();
	visitList_of_net_decl_assignments(lna, t, false, doc, res);
}

// @note same as visitList_of_net_identifiers but without the dimensions and with the default value
void VerModuleParser::visitList_of_net_decl_assignments(
		sv2017Parser::List_of_net_decl_assignmentsContext *ctx,
		iHdlExpr *base_type, bool is_latched, const string &doc,
		std::vector<HdlVariableDef*> &res) {
	// list_of_net_decl_assignments: net_decl_assignment ( COMMA net_decl_assignment )*;

	;
	VerTypeParser tp(commentParser);
	bool first = true;
	for (auto nd : ctx->net_decl_assignment()) {
		// net_decl_assignment:
		//  identifier ( unpacked_dimension )* ( ASSIGN expression )?;
		auto _id = nd->identifier();
		auto id = VerExprParser::getIdentifierStr(_id);
		iHdlExpr *def_val = nullptr;
		auto e = nd->expression();
		if (e)
			def_val = VerExprParser(commentParser).visitExpression(e);
		auto t = base_type;
		if (!first) {
			t = new iHdlExpr(*t);
		}
		auto uds = nd->unpacked_dimension();
		t = tp.applyUnpacked_dimension(t, uds);
		auto v = new HdlVariableDef(id, base_type, def_val);
		if (first) {
			v->__doc__ = doc;
			first = false;
		}

		v->is_latched = is_latched;
		res.push_back(v);
	}
}

}
}
