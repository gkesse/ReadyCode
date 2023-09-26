//===============================================
#include "GProcess.h"
#include "GHello.h"
#include "GTest.h"
//===============================================
static void GProcess_delete(GProcess** _this);
static void GProcess_inits(GProcess* _this);
static void GProcess_clean(GProcess* _this);
static void GProcess_run(GProcess* _this, int _argc, char** _argv);
static void GProcess_runHello(GProcess* _this, int _argc, char** _argv);
static void GProcess_runTest(GProcess* _this, int _argc, char** _argv);
//===============================================
GProcess* GProcess_new() {
    GProcess* lObj = (GProcess*)malloc(sizeof(GProcess));
    GProcess_init(lObj);
    return lObj;
}
//===============================================
void GProcess_init(GProcess* _this) {
    assert(_this);
    _this->delete = GProcess_delete;
    _this->inits = GProcess_inits;
    _this->clean = GProcess_clean;
    _this->run = GProcess_run;

    _this->m_obj = GObject_new();
}
//===============================================
static void GProcess_delete(GProcess** _this) {
    assert(*_this);
    GObject* lObj = (*_this)->m_obj;
    lObj->delete(&lObj);
    free(*_this);
    (*_this) = 0;
}
//===============================================
static void GProcess_inits(GProcess* _this) {
    assert(_this);
    SetConsoleOutputCP(CP_UTF8);
}
//===============================================
static void GProcess_clean(GProcess* _this) {
    assert(_this);
}
//===============================================
static void GProcess_run(GProcess* _this, int _argc, char** _argv) {
    assert(_this);
    char* lModule = "";
    if(_argc > 1) lModule = _argv[1];
    GLog* lLog = _this->m_obj->m_logs;

    if(!strcmp(lModule, "")) {
        lLog->addError(lLog, "Le module est obligatoire.");
    }
    else if(!strcmp(lModule, "hello")) {
        GProcess_runHello(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "test")) {
        GProcess_runTest(_this, _argc, _argv);
    }
    else {
        lLog->addError(lLog, "Le module est inconnu.");
    }
}
//===============================================
static void GProcess_runHello(GProcess* _this, int _argc, char** _argv) {
    assert(_this);
    GDEFINE_OBJ(GHello, lHello)
    lHello.sayHello();
}
//===============================================
static void GProcess_runTest(GProcess* _this, int _argc, char** _argv) {
    assert(_this);
    GDEFINE_OBJ(GTest, lObj)
    lObj.run(&lObj, _argc, _argv);
    _this->m_obj->m_logs->addLogs(_this->m_obj->m_logs, lObj.m_obj->m_logs);
}
//===============================================
