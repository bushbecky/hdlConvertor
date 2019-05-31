#pragma once
#include <vector>
#include "named.h"
#include "expr.h"
#include "position.h"
#include "iHdlObj.h"

namespace hdlConvertor {
namespace hdlObjects {

class CompInstance: public WithDoc, public WithPos, public iHdlObj {
public:
	Expr * name;
	Expr * entityName;
	std::vector<Expr*> genericMap;
	std::vector<Expr*> portMap;

	CompInstance(Expr * name, Expr * _entityName);
	~CompInstance();
};

}
}
