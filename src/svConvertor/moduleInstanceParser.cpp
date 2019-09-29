#include <hdlConvertor/svConvertor/moduleInstanceParser.h>

#include <hdlConvertor/notImplementedLogger.h>
#include <hdlConvertor/svConvertor/exprParser.h>
#include <hdlConvertor/svConvertor/moduleParamParser.h>

namespace hdlConvertor {
namespace sv {

using namespace std;
using sv2017Parser = sv2017_antlr::sv2017Parser;
using namespace hdlConvertor::hdlObjects;

vector<HdlCompInstance *> ModuleInstanceParser::visitModule_instantiation(
		sv2017Parser::Module_instantiationContext* ctx) {
	// module_instantiation
	//    : module_identifier (parameter_value_assignment)? module_instance (',' module_instance)* ';'
	//    ;
	auto module_name = ctx->module_identifier()->getText();

	auto pva = ctx->parameter_value_assignment();
	vector<iHdlExpr*> genericMap;
	if (pva) {
		// parameter_value_assignment
		//    : '#' '(' list_of_parameter_assignments ')'
		//    ;
		genericMap = visitList_of_parameter_assignments(
				pva->list_of_parameter_assignments());
	}
	auto mis = ctx->module_instance();
	bool first = true;
	vector<HdlCompInstance *> res;
	for (auto mi : mis) {
		HdlCompInstance * c;
		if (first) {
			c = visitModule_instance(mi, iHdlExpr::ID(module_name), genericMap);
			first = false;
		} else {
			vector<iHdlExpr*> gm;
			for (auto e : genericMap)
				gm.push_back(new iHdlExpr(*e));
			c = visitModule_instance(mi, iHdlExpr::ID(module_name), gm);
		}
		res.push_back(c);
	}
	return res;
}

vector<iHdlExpr*> ModuleInstanceParser::visitList_of_parameter_assignments(
		sv2017Parser::List_of_parameter_assignmentsContext * ctx) {

	// list_of_parameter_assignments
	//    : ordered_parameter_assignment (',' ordered_parameter_assignment)*
	//    | named_parameter_assignment (',' named_parameter_assignment)*
	//    ;

	//   ctx->parameter_identifier()->identifier()->getText()

	vector<iHdlExpr*> pcs;
	auto opa = ctx->ordered_parameter_assignment();
	if (opa.size()) {
		for (auto pa : opa) {
			// ordered_parameter_assignment
			//    : expression
			//    ;
			auto e = VerExprParser::visitExpression(pa->expression());
			pcs.push_back(e);
		}
	} else {
		auto npa = ctx->named_parameter_assignment();
		for (auto pa : npa) {
			// named_parameter_assignment
			//    : '.' parameter_identifier '(' (expression)? ')'
			//    ;
			auto k = ModuleParamParser::visitParameter_identifier(
					pa->parameter_identifier());
			iHdlExpr * v;
			auto e = pa->expression();
			if (e) {
				v = VerExprParser::visitExpression(e);
			} else {
				v = iHdlExpr::null();
			}
			pcs.push_back(new iHdlExpr(k, HdlOperatorType::MAP_ASSOCIATION, v));
		}
	}
	return pcs;
}

HdlCompInstance * ModuleInstanceParser::visitModule_instance(
		sv2017Parser::Module_instanceContext * ctx, iHdlExpr * module_id,
		vector<iHdlExpr*> genericMap) {
	// @note genericMap became the owner of all Expr instances in the vector
	//       that means that the instances can not be shared

	// module_instance
	//    : name_of_instance '(' list_of_port_connections ')'
	//    ;
	auto noi = ctx->name_of_instance();
	// name_of_instance
	//    : module_instance_identifier (range_)?
	//    ;
	// module_instance_identifier
	//    : arrayed_identifier
	//    ;
	auto name = VerExprParser::visitArrayed_identifier(
			noi->module_instance_identifier()->arrayed_identifier());
	auto _r = noi->range_();
	if (_r) {
		auto r = VerExprParser::visitRange_(_r);
		name = new iHdlExpr(name, HdlOperatorType::INDEX, r);
	}
	vector<iHdlExpr*> portMap = visitList_of_port_connections(
			ctx->list_of_port_connections());
	auto c = new HdlCompInstance(name, module_id);
	c->genericMap = genericMap;
	c->portMap = portMap;
	return c;
}

vector<iHdlExpr*> ModuleInstanceParser::visitList_of_port_connections(
		sv2017Parser::List_of_port_connectionsContext * ctx) {
	// list_of_port_connections
	//    : ordered_port_connection (',' ordered_port_connection)*
	//    | named_port_connection (',' named_port_connection)*
	//    ;
	//
	vector<iHdlExpr*> pcs;
	auto opc = ctx->ordered_port_connection();
	if (opc.size()) {
		for (auto pc : opc) {
			// ordered_port_connection
			//    : attribute_instance* (expression)?
			//    ;
			//
			if (pc->attribute_instance().size())
				NotImplementedLogger::print(
						"ModuleInstanceParser.visitList_of_port_connections.ordered_port_connection attribute_instance",
						pc);
			auto _e = pc->expression();
			iHdlExpr * e;
			if (_e) {
				e = VerExprParser::visitExpression(_e);
			} else {
				e = iHdlExpr::null();
			}
			pcs.push_back(e);
		}
	} else {
		auto npc = ctx->named_port_connection();
		for (auto pc : npc) {
			// named_port_connection
			//    : attribute_instance* '.' identifier '(' (expression)? ')'
			//    ;
			// port_identifier : identifier;
			if (pc->attribute_instance().size())
				NotImplementedLogger::print(
						"ModuleInstanceParser.visitList_of_port_connections.named_port_connection attribute_instance",
						pc);

			iHdlExpr * k = VerExprParser::visitIdentifier(
					pc->identifier());
			iHdlExpr * v;
			auto e = pc->expression();
			if (e) {
				v = VerExprParser::visitExpression(e);
			} else {
				v = iHdlExpr::null();
			}
			pcs.push_back(new iHdlExpr(k, HdlOperatorType::MAP_ASSOCIATION, v));
		}
	}
	return pcs;
}

}
}
