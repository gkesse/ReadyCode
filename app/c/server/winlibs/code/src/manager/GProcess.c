//===============================================
#include "GProcess.h"
#include "GTest.h"
#include "GSocket.h"
//===============================================
static void GProcess_delete(GProcess* _this);
static void GProcess_init(GProcess* _this);
static void GProcess_clean(GProcess* _this);
static void GProcess_run(GProcess* _this, int _argc, char** _argv);
static void GProcess_runTest(GProcess* _this, int _argc, char** _argv);
static void GProcess_runServer(GProcess* _this, int _argc, char** _argv);
//===============================================
GProcess* GProcess_new() {
    GProcess* lObj = (GProcess*)malloc(sizeof(GProcess));
    lObj->m_obj = GObject_new();

    lObj->delete = GProcess_delete;
    lObj->init = GProcess_init;
    lObj->clean = GProcess_clean;
    lObj->run = GProcess_run;
    lObj->runTest = GProcess_runTest;
    lObj->runServer = GProcess_runServer;
    return lObj;
}
//===============================================
static void GProcess_delete(GProcess* _this) {
    assert(_this);
    _this->m_obj->delete(_this->m_obj);
    free(_this);
}
//===============================================
static void GProcess_init(GProcess* _this) {
    assert(_this);
    SetConsoleOutputCP(CP_UTF8);
    xmlInitParser();
    xmlKeepBlanksDefault(0);
}
//===============================================
static void GProcess_clean(GProcess* _this) {
    assert(_this);
    xmlCleanupParser();
    xmlMemoryDump();
    GFunctions_delete();
}
//===============================================
static void GProcess_run(GProcess* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;
    const char* lModule = "";
    if(_argc > 1) lModule = _argv[1];

    if(!strcmp(lModule, "")) {
        lLog->addError(lLog, "Le module est obligatoire.");
    }
    else if(!strcmp(lModule, "test")) {
        _this->runTest(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "server")) {
        _this->runServer(_this, _argc, _argv);
    }
    else {
        lLog->addError(lLog, "Le module est inconnu.");
    }

    lLog->showLogsX(lLog);
}
//===============================================
static void GProcess_runTest(GProcess* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;
    GTest* lObj = GTest_new();
    lObj->run(lObj, _argc, _argv);
    lLog->addLogs(lLog, lObj->m_obj->m_logs);
    lObj->delete(lObj);
}
//===============================================
static void GProcess_runServer(GProcess* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;
    GSocket* lObj = GSocket_new();
    lObj->run(lObj, _argc, _argv);
    lLog->addLogs(lLog, lObj->m_parent->m_logs);
    lObj->delete(lObj);
}
//===============================================
