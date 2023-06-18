//===============================================
#include "GFunctions.h"
//===============================================
static PyObject* method_callFacade(PyObject* _self, PyObject* _args);
PyMODINIT_FUNC PyInit_rdvcpy(void);
//===============================================
static PyMethodDef method_defs[] = {
    {"callFacade", method_callFacade, METH_VARARGS, "Interface Extension C pour Python par ReadyDev"},
    {NULL, NULL, 0, NULL}
};
//===============================================
static struct PyModuleDef module_defs = {
    PyModuleDef_HEAD_INIT,
    "rdvcpy",
    "Module Extension C pour Python par ReadyDev",
    -1,
    method_defs
};
//===============================================
PyMODINIT_FUNC PyInit_rdvcpy(void) {
    return PyModule_Create(&module_defs);
}
//===============================================
static PyObject* method_callFacade(PyObject* _self, PyObject* _args) {
    const char* lModule;
    const char* lMethod;
    const char* lData;

    if(!PyArg_ParseTuple(_args, "sss", &lModule, &lMethod, &lData)) {
        return NULL;
    }

    char* lBuffer = sformat("%s - %s - %s", lModule, lMethod, lData);
    PyObject* lObject = PyBytes_FromString(lBuffer);
    GFunctions_delete();

    return lObject;
}
//===============================================
