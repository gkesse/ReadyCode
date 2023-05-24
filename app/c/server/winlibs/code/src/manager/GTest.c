//===============================================
#include "GTest.h"
#include "GVector.h"
#include "GLog.h"
#include "GSocket.h"
#include "GString.h"
//===============================================
static void GTest_delete(GTest* _this);
static void GTest_run(GTest* _this, int _argc, char** _argv);
static void GTest_runVector(GTest* _this, int _argc, char** _argv);
static void GTest_runLog(GTest* _this, int _argc, char** _argv);
static void GTest_runSocketClient(GTest* _this, int _argc, char** _argv);
static void GTest_runString(GTest* _this, int _argc, char** _argv);
//===============================================
GTest* GTest_new() {
    GTest* lObj = (GTest*)malloc(sizeof(GTest));
    lObj->m_parent = GObject_new();
    lObj->delete = GTest_delete;
    lObj->run = GTest_run;
    lObj->runVector = GTest_runVector;
    lObj->runLog = GTest_runLog;
    lObj->runSocketClient = GTest_runSocketClient;
    lObj->runString = GTest_runString;
    return lObj;
}
//===============================================
static void GTest_delete(GTest* _this) {
    assert(_this);
    _this->m_parent->delete(_this->m_parent);
    free(_this);
}
//===============================================
static void GTest_run(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    const char* lModule = "";
    if(_argc > 2) lModule = _argv[2];

    if(!strcmp(lModule, "vector")) {
        _this->runVector(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "log")) {
        _this->runLog(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "socket_client")) {
        _this->runSocketClient(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "string")) {
        _this->runString(_this, _argc, _argv);
    }
}
//===============================================
static void GTest_runVector(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GVector* lMap = GVector_new();

    lMap->add(lMap, (void*)10);
    lMap->add(lMap, (void*)100);
    lMap->add(lMap, (void*)1000);

    printf("%d\n", lMap->get(lMap, 0));
    printf("%d\n", lMap->get(lMap, 1));
    printf("%d\n", lMap->get(lMap, 2));

    printf("%d\n", lMap->size(lMap));

    lMap->clear(lMap);
    lMap->delete(lMap);
}
//===============================================
static void GTest_runLog(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = GLog_new();

    lLog->addError(lLog, "Le module est obligatoire.");
    lLog->addData(lLog, "Le base de données est hors service.");
    lLog->addLog(lLog, "Le serveur est insdisponible.");

    lLog->showLogsA(lLog);

    lLog->clear(lLog);
    lLog->delete(lLog);
}
//===============================================
static void GTest_runSocketClient(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_parent->m_logs;
    GSocket* lClient = GSocket_new();
    GString* lData = GString_new();

    lClient->callServer(lClient, "Bonjour tout le monde", lData);
    lLog->addLogs(lLog, lClient->m_parent->m_logs);
    lData->print(lData);

    lData->delete(lData);
    lClient->delete(lClient);
}
//===============================================
static void GTest_runString(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_parent->m_logs;

    GString* lData = GString_new();

    lData->create(lData, "Bonjour tout le monde");
    lData->print(lData);

    lData->add(lData, ", Bonjour tout le monde");
    lData->add(lData, ", Bonjour tout le monde");
    lData->add(lData, ", Bonjour tout le monde");
    lData->print(lData);

    lData->format(lData, "Un : %d ; Deux : %d, Trois : %s", 1, 2, "Three");
    lData->print(lData);

    lData->delete(lData);
}
//===============================================
