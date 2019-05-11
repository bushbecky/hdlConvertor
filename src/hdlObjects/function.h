#pragma once
#include <vector>
#include "named.h"
#include "expr.h"
#include "variable.h"
#include "statement.h"

namespace hdlConvertor {
namespace hdlObjects {

class Function: public WithNameAndDoc {
	bool isOperator;
	Expr * returnT;
	std::vector<Variable*> * params;
public:
	std::vector<Variable*> locals;
	std::vector<Statement*> body;

	Function(char * name, bool isOperator, Expr * returnT,
			std::vector<Variable*> * params);
#ifdef USE_PYTHON
	PyObject * toJson() const;
#endif
	~Function();
};

}
}
