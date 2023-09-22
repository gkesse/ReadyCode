//===============================================
#include "GProcess.h"
#include "GHello.h"
#include "GTest.h"
//===============================================
static void GProcess_delete(GProcess** _obj);
static void GProcess_run(int _argc, char** _argv);
static void GProcess_runHello(int _argc, char** _argv);
static void GProcess_runTest(int _argc, char** _argv);
//===============================================
GProcess* GProcess_new() {
    GProcess* lObj = (GProcess*)malloc(sizeof(GProcess));
    GProcess_init(lObj);
    return lObj;
}
//===============================================
static void GProcess_delete(GProcess** _obj) {
    free(*_obj);
    (*_obj) = 0;
}
//===============================================
void GProcess_init(GProcess* _obj) {
    _obj->delete = GProcess_delete;
    _obj->run = GProcess_run;
}
//===============================================
static void GProcess_run(int _argc, char** _argv) {
    char* lModule = "";
    if(_argc > 1) lModule = _argv[1];
    if(!strcmp(lModule, "hello")) {
        GProcess_runHello(_argc, _argv);
    }
    else if(!strcmp(lModule, "test")) {
        GProcess_runTest(_argc, _argv);
    }
}
//===============================================
static void GProcess_runHello(int _argc, char** _argv) {
    GDEFINE_OBJ(GHello, lHello)
    lHello.sayHello();
}
//===============================================
static void GProcess_runTest(int _argc, char** _argv) {
    GDEFINE_OBJ(GTest, lObj)
    lObj.run(_argc, _argv);
}
//===============================================
