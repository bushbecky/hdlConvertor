#pragma once

#include <memory>

#include <hdlConvertor/hdlObjects/named.h>
#include <hdlConvertor/hdlObjects/iHdlObj.h>


namespace hdlConvertor {
namespace hdlObjects {

/*
 * Interface for data of HDL expression
 * */
class iHdlExprItem: public WithPos, public iHdlObj {
protected:
	iHdlExprItem() {};
public:
	// iHdlExprItem(const iHdlExprItem & rhs) = delete;
	// a method which acts like virtual copy constructor (deepcopy)
	virtual iHdlExprItem * clone() const = 0;
	virtual std::unique_ptr<iHdlExprItem> clone_uniq() {
		return std::unique_ptr<iHdlExprItem>(clone());
	};

	virtual ~iHdlExprItem() {
	}
};

}
}
