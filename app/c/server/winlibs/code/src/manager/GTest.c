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
static void GTest_runFunctions(GTest* _this, int _argc, char** _argv);
static void GTest_runVector(GTest* _this, int _argc, char** _argv);
static void GTest_runLog(GTest* _this, int _argc, char** _argv);
static void GTest_runSocketClient(GTest* _this, int _argc, char** _argv);
static void GTest_runString(GTest* _this, int _argc, char** _argv);
static void GTest_runXml(GTest* _this, int _argc, char** _argv);
static void GTest_runJson(GTest* _this, int _argc, char** _argv);
static void GTest_runCode(GTest* _this, int _argc, char** _argv);
static void GTest_runModule(GTest* _this, int _argc, char** _argv);
static void GTest_runRequest(GTest* _this, int _argc, char** _argv);
static void GTest_runFacade(GTest* _this, int _argc, char** _argv);
static void GTest_runIconv(GTest* _this, int _argc, char** _argv);
//===============================================
GTest* GTest_new() {
    GTest* lObj = (GTest*)malloc(sizeof(GTest));
    lObj->m_obj = GObject_new();

    lObj->delete = GTest_delete;
    lObj->run = GTest_run;
    lObj->runFunctions = GTest_runFunctions;
    lObj->runVector = GTest_runVector;
    lObj->runLog = GTest_runLog;
    lObj->runSocketClient = GTest_runSocketClient;
    lObj->runString = GTest_runString;
    lObj->runXml = GTest_runXml;
    lObj->runJson = GTest_runJson;
    lObj->runCode = GTest_runCode;
    lObj->runModule = GTest_runModule;
    lObj->runRequest = GTest_runRequest;
    lObj->runFacade = GTest_runFacade;
    lObj->runIconv = GTest_runIconv;
    return lObj;
}
//===============================================
static void GTest_delete(GTest* _this) {
    assert(_this);
    _this->m_obj->delete(_this->m_obj);
    free(_this);
}
//===============================================
static void GTest_run(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;
    const char* lModule = "";
    if(_argc > 2) lModule = _argv[2];

    if(!strcmp(lModule, "")) {
        lLog->addError(lLog, "La méthode est obligatoire.");
    }
    else if(!strcmp(lModule, "functions")) {
        _this->runFunctions(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "vector")) {
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
    else if(!strcmp(lModule, "code")) {
        _this->runCode(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "module")) {
        _this->runModule(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "request")) {
        _this->runRequest(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "facade")) {
        _this->runFacade(_this, _argc, _argv);
    }
    else {
        lLog->addError(lLog, "La méthode est inconnue.");
    }
}
//===============================================
static void GTest_runFunctions(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    printf("%s\n", sformat("Acceuil : %s", "Bonjour tout le monde"));
    printf("%s\n", sformat("Année : %d", 2023));
    printf("%s\n", sformat("PI : %.2f", 3.14));
}
//===============================================
static void GTest_runVector(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GVector* lMap = GVector_new();

    // add
    lMap->add(lMap, (void*)10);
    lMap->add(lMap, (void*)100);
    lMap->add(lMap, (void*)1000);

    // get
    printf("%d\n", lMap->get(lMap, 0));
    printf("%d\n", lMap->get(lMap, 1));
    printf("%d\n", lMap->get(lMap, 2));

    // size
    printf("%d\n", lMap->size(lMap));

    lMap->clear(lMap);
    lMap->delete(lMap);
}
//===============================================
static void GTest_runLog(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = GLog_new();

    // addError - addData - addLog
    lLog->addError(lLog, "Le module est obligatoire.");
    lLog->addData(lLog, "Le base de données est hors service.");
    lLog->addLog(lLog, "Le serveur est insdisponible.");

    // showLogsA
    lLog->showLogsA(lLog);

    lLog->clear(lLog);
    lLog->delete(lLog);
}
//===============================================
static void GTest_runSocketClient(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;
    GSocket* lClient = GSocket_new();
    GString* lData = GString_new();

    // callServer
    lClient->callServer(lClient, "Bonjour tout le monde", lData);
    lLog->addLogs(lLog, lClient->m_parent->m_logs);
    lData->print(lData);

    lData->delete(lData);
    lClient->delete(lClient);
}
//===============================================
static void GTest_runString(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;
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
    GLog* lLog = _this->m_obj->m_logs;
    GXml* lXml = GXml_new();
    GXml* lObj = GXml_new();
    GXml* lObj2 = GXml_new();

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
    lObj->m_node = lXml->addObj(lXml, "program");
    lObj->addData(lObj, "lang", "c");
    lObj->addData(lObj, "module", "xml");
    lObj->addData(lObj, "library", "libxml2");
    lXml->print(lXml);

    // createDoc - addObj - [ addObj - addData ]
    lXml->createDoc(lXml);
    lObj->m_node = lXml->addObj(lXml, "data");
    lObj2->m_node = lObj->addObj(lObj, "program");
    lObj2->addData(lObj2, "lang", "c");
    lObj2->addData(lObj2, "module", "xml");
    lObj2->addData(lObj2, "library", "libxml2");
    lObj2->m_node = lObj->addObj(lObj, "program");
    lObj2->addData(lObj2, "lang", "c");
    lObj2->addData(lObj2, "module", "xml");
    lObj2->addData(lObj2, "library", "libxml2");
    lXml->print(lXml);

    // createDoc - createNode
    lXml->createDoc(lXml);
    lObj->m_node = lXml->createNode(lXml, lXml, "/rdv/data/code", "");
    lObj->m_node = lXml->createNode(lXml, lXml, "/rdv/data/code", "");
    lObj->createNode(lObj, lXml, "rdv/data/code", "");
    lObj->createNode(lObj, lXml, "rdv/data/code", "");
    lXml->print(lXml);

    lObj->delete(lObj);
    lObj2->delete(lObj2);
    lXml->delete(lXml);
}
//===============================================
static void GTest_runJson(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;
    GJson* lJson = GJson_new();
    GJson* lJsonC1 = GJson_new();
    GJson* lJsonC2 = GJson_new();

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
    lJsonC1->m_json = lJson->addObjObj(lJson, "program");
    lJsonC1->addObjData(lJsonC1, "lang", "c");
    lJsonC1->addObjData(lJsonC1, "module", "json");
    lJsonC1->addObjData(lJsonC1, "library", "json-c");
    lJson->print(lJson);

    // createArr - addArrData
    lJson->createArr(lJson);
    lJson->addArrData(lJson, "lang");
    lJson->addArrData(lJson, "module");
    lJson->addArrData(lJson, "library");
    lJson->print(lJson);

    // createObj - createArr - addArrData
    lJson->createObj(lJson);
    lJsonC1->m_json  = lJson->addObjArr(lJson, "program");
    lJsonC1->addArrData(lJsonC1, "lang");
    lJsonC1->addArrData(lJsonC1, "module");
    lJsonC1->addArrData(lJsonC1, "library");
    lJson->print(lJson);

    // createObj - createArr - addArrData
    lJson->createObj(lJson);
    lJsonC1->m_json  = lJson->addObjArr(lJson, "program");
    lJsonC2->m_json  = lJsonC1->addArrObj(lJsonC1);
    lJsonC2->addObjData(lJsonC2, "lang", "c");
    lJsonC2->addObjData(lJsonC2, "module", "json");
    lJsonC2->addObjData(lJsonC2, "library", "json-c");
    lJsonC2->m_json  = lJsonC1->addArrObj(lJsonC1);
    lJsonC2->addObjData(lJsonC2, "lang", "c");
    lJsonC2->addObjData(lJsonC2, "module", "json");
    lJsonC2->addObjData(lJsonC2, "library", "json-c");
    lJson->print(lJson);

    lJson->delete(lJson);
    lJsonC1->delete(lJsonC1);
    lJsonC2->delete(lJsonC2);
}
//===============================================
static void GTest_runCode(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;
    GCode* lDom = GCode_new();
    lDom->m_dom->createDoc(lDom->m_dom);

    // createDatas
    lDom->createDatas(lDom);
    lDom->createDatas(lDom);
    lDom->m_dom->print(lDom->m_dom);

    // createDatas
    lDom->createCode(lDom, "manager");
    lDom->createCode(lDom, "page");
    lDom->createCode(lDom, "manager");
    lDom->createCode(lDom, "page");
    lDom->m_dom->print(lDom->m_dom);

    // addData
    lDom->addData(lDom, "manager", "module", "page");
    lDom->addData(lDom, "manager", "method", "save_page_file");
    lDom->addData(lDom, "manager", "module", "page");
    lDom->addData(lDom, "manager", "method", "save_page_file");
    lDom->m_dom->print(lDom->m_dom);

    lDom->delete(lDom);
}
//===============================================
static void GTest_runModule(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = GLog_new();
    GLog* lLog2 = GLog_new();
    GString* lData = GString_new();

    // addError - addLog - addData
    lLog->addError(lLog, "La connexion au serveur a echoué.");
    lLog->addLog(lLog, "La lecture du fichier a réussi.");
    lLog->addData(lLog, "La serveur n'a pas été initialisé.");
    lLog->showLogsA(lLog);

    // loadFromMap - serialize
    lLog->loadFromMap(lLog, 3);
    lData->assign(lData, lLog->serialize(lLog));
    lData->print(lData);

    // loadToMap - serialize
    lLog->m_msg = "Le serveur a été mis à jour.";
    lLog->loadToMap(lLog, 3);
    lData->assign(lData, lLog->serialize(lLog));
    lData->print(lData);

    // loadToMap - serialize
    lLog->m_msg = "Le serveur a été mis à jour.";
    lLog->loadToMap(lLog, 3);
    lData->assign(lData, lLog->serialize(lLog));
    lData->print(lData);

    // deserialize - serialize
    lLog2->deserialize(lLog2, lData->m_data);
    lData->assign(lData, lLog2->serialize(lLog2));
    lData->assign(lData, lData->toJson(lData));
    lData->print(lData);

    lLog->delete(lLog);
    lData->delete(lData);
}
//===============================================
static void GTest_runRequest(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GCode* lDom = GCode_new();
    GCode* lDomC = GCode_new();
    GXml* lNode = GXml_new();
    GXml* lNodeC = GXml_new();
    GLog* lLog = GLog_new();
    GString* lData = GString_new();

    // addError - addLog - addData
    lLog->addError(lLog, "La connexion au serveur a echoué.");
    lLog->addLog(lLog, "La lecture du fichier a réussi.");
    lLog->addData(lLog, "La serveur n'a pas été initialisé.");
    lData->assign(lData, lLog->serialize(lLog));
    lLog->print(lLog);

    // createDoc - addData
    lDom->m_dom->createDoc(lDom->m_dom);
    lDom->addData(lDom, "manager", "module", "log");
    lDom->addData(lDom, "manager", "method", "save_logs");
    lNode->m_node = lDom->createDatas(lDom);
    lDomC->m_dom->loadXml(lDomC->m_dom, lData->m_data);
    lNodeC->m_node = lDomC->createDatas(lDomC);
    lData->assign(lData, lNodeC->toNode(lNodeC, lDomC->m_dom));
    lNode->loadNode(lNode, lData->m_data);
    lDom->m_dom->print(lDom->m_dom);

    lDom->delete(lDom);
    lDomC->delete(lDomC);
    lNode->delete(lNode);
    lNodeC->delete(lNodeC);
    lLog->delete(lLog);
}
//===============================================
static void GTest_runFacade(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = GLog_new();

    // addError - addLog - addData - saveLogs
    lLog->addError(lLog, "La connexion au serveur a echoué.");
    lLog->addLog(lLog, "La lecture du fichier a réussi.");
    lLog->addData(lLog, "La serveur n'a pas été initialisé.");
    lLog->saveLogs(lLog);
    _this->m_obj->m_logs->addLogs(_this->m_obj->m_logs, lLog);

    lLog->delete(lLog);
}
//===============================================
static void GTest_runIconv(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    GString* lData = GString_new();

    lData->create(lData, "Le module a été trouvé");
    lData->print(lData);
    lData->toUtf8(lData);
    lData->print(lData);

    lData->delete(lData);
}
//===============================================
