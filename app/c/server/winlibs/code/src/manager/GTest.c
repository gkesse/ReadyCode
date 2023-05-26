//===============================================
#include "GTest.h"
#include "GVector.h"
#include "GLog.h"
#include "GSocket.h"
#include "GString.h"
#include "GXml.h"
#include "GJson.h"
//===============================================
static void GTest_delete(GTest* _this);
static void GTest_run(GTest* _this, int _argc, char** _argv);
static void GTest_runVector(GTest* _this, int _argc, char** _argv);
static void GTest_runLog(GTest* _this, int _argc, char** _argv);
static void GTest_runSocketClient(GTest* _this, int _argc, char** _argv);
static void GTest_runString(GTest* _this, int _argc, char** _argv);
static void GTest_runXml(GTest* _this, int _argc, char** _argv);
static void GTest_runJson(GTest* _this, int _argc, char** _argv);
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
    lObj->runXml = GTest_runXml;
    lObj->runJson = GTest_runJson;
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
    else if(!strcmp(lModule, "xml")) {
        _this->runXml(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "json")) {
        _this->runJson(_this, _argc, _argv);
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
    GVector* lMap = 0;

    // create
    lData->create(lData, "Bonjour tout le monde");
    lData->print(lData);

    // add
    lData->add(lData, ", Bonjour tout le monde");
    lData->add(lData, ", Bonjour tout le monde");
    lData->add(lData, ", Bonjour tout le monde");
    lData->print(lData);

    // format
    lData->format(lData, "Un : %d ; Deux : %d, Trois : %s", 1, 2, "Three");
    lData->print(lData);

    // split
    lMap = lData->split(lData, "run/data/code", "/");
    lMap->print(lMap);

    lData->delete(lData);
    lMap->delete(lMap);
}
//===============================================
static void GTest_runXml(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_parent->m_logs;
    GXml* lXml = GXml_new();
    GXml* lObj = 0;
    GXml* lObj2 = 0;

    // loadFile
    lXml->loadFile(lXml, "./data/test/test.xml");
    lXml->print(lXml);

    // createDoc - addData
    lXml->createDoc(lXml);
    lXml->addData(lXml, "lang", "c");
    lXml->addData(lXml, "module", "xml");
    lXml->addData(lXml, "library", "libxml2");
    lXml->print(lXml);

    // createDoc - addObj - addData
    lXml->createDoc(lXml);
    lObj = lXml->addObj(lXml, "program");
    lObj->addData(lObj, "lang", "c");
    lObj->addData(lObj, "module", "xml");
    lObj->addData(lObj, "library", "libxml2");
    lXml->print(lXml);

    // createDoc - addObj - [ addObj - addData ]
    lXml->createDoc(lXml);
    lObj = lXml->addObj(lXml, "data");
    lObj2 = lObj->addObj(lObj, "program");
    lObj2->addData(lObj2, "lang", "c");
    lObj2->addData(lObj2, "module", "xml");
    lObj2->addData(lObj2, "library", "libxml2");
    lObj2 = lObj->addObj(lObj, "program");
    lObj2->addData(lObj2, "lang", "c");
    lObj2->addData(lObj2, "module", "xml");
    lObj2->addData(lObj2, "library", "libxml2");
    lXml->print(lXml);

    lXml->delete(lXml);
}
//===============================================
static void GTest_runJson(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_parent->m_logs;
    GJson* lJson = GJson_new();
    GJson* lObj = 0;
    GJson* lObj2 = 0;

    // loadFile
    lJson->loadFile(lJson, "./data/test/test.json");
    lJson->print(lJson);

    // createObj - addObjData
    lJson->createObj(lJson);
    lJson->addObjData(lJson, "lang", "c");
    lJson->addObjData(lJson, "module", "json");
    lJson->addObjData(lJson, "library", "json-c");
    lJson->print(lJson);

    // createObj - addObjObj - addObjData
    lJson->createObj(lJson);
    lObj = lJson->addObjObj(lJson, "program");
    lObj->addObjData(lObj, "lang", "c");
    lObj->addObjData(lObj, "module", "json");
    lObj->addObjData(lObj, "library", "json-c");
    lJson->print(lJson);

    // createArr - addArrData
    lJson->createArr(lJson);
    lJson->addArrData(lJson, "lang");
    lJson->addArrData(lJson, "module");
    lJson->addArrData(lJson, "library");
    lJson->print(lJson);

    // createObj - createArr - addArrData
    lJson->createObj(lJson);
    lObj = lJson->addObjArr(lJson, "program");
    lObj->addArrData(lObj, "lang");
    lObj->addArrData(lObj, "module");
    lObj->addArrData(lObj, "library");
    lJson->print(lJson);

    // createObj - createArr - addArrData
    lJson->createObj(lJson);
    lObj = lJson->addObjArr(lJson, "program");
    lObj2 = lObj->addArrObj(lObj);
    lObj2->addObjData(lObj2, "lang", "c");
    lObj2->addObjData(lObj2, "module", "json");
    lObj2->addObjData(lObj2, "library", "json-c");
    lObj2 = lObj->addArrObj(lObj);
    lObj2->addObjData(lObj2, "lang", "c");
    lObj2->addObjData(lObj2, "module", "json");
    lObj2->addObjData(lObj2, "library", "json-c");
    lJson->print(lJson);

    lJson->delete(lJson);
}
//===============================================
