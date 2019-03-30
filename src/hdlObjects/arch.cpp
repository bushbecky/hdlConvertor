#include "arch.h"

#ifdef USE_PYTHON
PyObject * Arch::toJson() const {
	PyObject * o = Named::toJson();
	JSN_DEBUG("Arch - name")
	PyDict_SetItemString(o, "name", PyUnicode_FromString(name));

	JSN_DEBUG("Arch - entityName")
	PyDict_SetItemString(o, "entityName", PyUnicode_FromString(entityName));

	JSN_DEBUG("Arch - variables")
	addJsonArrP(o, "variables", varialbles);

	JSN_DEBUG("Arch - componentInstances")
	addJsonArrP(o, "componentInstances", componentInstances);

	JSN_DEBUG("Arch - statements")
	addJsonArrP(o, "statements", statements);

	return o;
}
#endif

Arch::~Arch() {
	for (auto c : componentInstances)
		delete c;
	for (auto s : statements)
		delete s;
	for (auto v : varialbles)
		delete v;
}
