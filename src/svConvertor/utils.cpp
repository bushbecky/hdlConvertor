#include <hdlConvertor/svConvertor/utils.h>

#include <hdlConvertor/svConvertor/exprParser.h>
#include <hdlConvertor/hdlObjects/hdlValue.h>
#include <hdlConvertor/svConvertor/sv2017Parser/sv2017Lexer.h>

#include <hdlConvertor/createObject.h>

using sv2017Parser = sv2017_antlr::sv2017Parser;
using namespace hdlConvertor::hdlObjects;
using namespace std;

namespace hdlConvertor {
namespace sv {

unique_ptr<iHdlExpr> Utils::mkStringT() {
	return iHdlExpr::ID("__str__");
}

unique_ptr<iHdlExpr> Utils::mkIntT() {
	return iHdlExpr::ID("integer");
}

unique_ptr<iHdlExpr> Utils::mkWireT() {
	return iHdlExpr::ID("wire");
}

unique_ptr<iHdlExpr> Utils::mkWireT(antlr4::ParserRuleContext *const ctx,
		unique_ptr<iHdlExpr> range, SIGNING_VAL signed_) {
	return mkWireT(ctx, nullptr, move(range), signed_);
}
std::unique_ptr<hdlObjects::iHdlExpr> Utils::signing(SIGNING_VAL signed_) {
	if (signed_ == SIGNING_VAL::NO_SIGN) {
		return iHdlExpr::null();
	} else {
		return iHdlExpr::INT(nullptr, signed_ ? 1 : 0);
	}
}
unique_ptr<iHdlExpr> Utils::mkWireT(antlr4::ParserRuleContext *const ctx,
		unique_ptr<iHdlExpr> net_type, unique_ptr<iHdlExpr> range,
		SIGNING_VAL signed_) {
	vector<unique_ptr<iHdlExpr>> operands;
	operands.push_back(move(range));
	operands.push_back(signing(signed_));
	if (net_type == nullptr)
		net_type = mkWireT();
	return iHdlExpr::parametrization(ctx, move(net_type), operands);
}

unique_ptr<iHdlExpr> append_expr(antlr4::ParserRuleContext *const ctx,
		unique_ptr<iHdlExpr> selected_name,
		HdlOperatorType operator_to_join_with, unique_ptr<iHdlExpr> new_part) {
	if (selected_name) {
		return create_object<iHdlExpr>(ctx, move(selected_name),
				operator_to_join_with, move(new_part));
	} else {
		return new_part;
	}
}

unique_ptr<iHdlExpr> reduce(vector<unique_ptr<iHdlExpr>> &ops,
		HdlOperatorType op) {
	unique_ptr<iHdlExpr> res = nullptr;
	for (auto &p : ops) {
		if (res == nullptr)
			res = move(p);
		else
			res = make_unique<iHdlExpr>(move(res), op, move(p));
	}
	return res;
}

}
}
