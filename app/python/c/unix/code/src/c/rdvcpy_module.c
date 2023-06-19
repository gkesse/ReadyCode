//===============================================
#include "GFunctions.h"
#include "GServer.h"
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

    GServer* lServer = GServer_new();
    GString* lResult = GString_new();
    lServer->run(lServer, lModule, lMethod, lData);
    lResult->assign(lResult, lServer->toString(lServer));
    PyObject* lObject = PyBytes_FromString(lResult->m_data);
    lServer->delete(lServer);
    lResult->delete(lResult);
    GFunctions_delete();

    return lObject;
}
//===============================================
