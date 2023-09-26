//===============================================
#include "GTest.h"
#include "GSocket.h"
#include "GFunctions.h"
//===============================================
static void GTest_delete(GTest** _this);
static void GTest_run(GTest* _this, int _argc, char** _argv);
static void GTest_runString(GTest* _this, int _argc, char** _argv);
static void GTest_runVector(GTest* _this, int _argc, char** _argv);
static void GTest_runLog(GTest* _this, int _argc, char** _argv);
static void GTest_runSocket(GTest* _this, int _argc, char** _argv);
//===============================================
GTest* GTest_new() {
    GTest* lObj = (GTest*)malloc(sizeof(GTest));
    GTest_init(lObj);
    return lObj;
}
//===============================================
void GTest_init(GTest* _this) {
    assert(_this);
    _this->delete = GTest_delete;
    _this->run = GTest_run;

    _this->m_obj = GObject_new();
}
//===============================================
static void GTest_delete(GTest** _this) {
    assert(*_this);
    GObject* lObj = (*_this)->m_obj;
    lObj->delete(&lObj);
    free(*_this);
    (*_this) = 0;
}
//===============================================
static void GTest_run(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    char* lModule = "";
    if(_argc > 2) lModule = _argv[2];
    GLog* lLog = _this->m_obj->m_logs;

    if(!strcmp(lModule, "")) {
        lLog->addError(lLog, "Le module est obligatoire.");
    }
    else if(!strcmp(lModule, "string")) {
        GTest_runString(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "vector")) {
        GTest_runVector(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "log")) {
        GTest_runLog(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "socket")) {
        GTest_runSocket(_this, _argc, _argv);
    }
    else {
        lLog->addError(lLog, "Le module est inconnu.");
    }
}
//===============================================
static void GTest_runString(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    printf("%s...\n",  __PRETTY_FUNCTION__);

    GString* lString = GString_new();
    GString* lString2 = GString_new();
    GString* lString3 = GString_new();
    GVector* lMap = GVector_new();

    lString->create(lString, "Voici mon premier message.\n");

    lString->add(lString, "Voici mon deuxième message.\n");
    lString->add(lString, "Voici mon troisième message.\n");
    lString->add(lString, "Voici mon quatrième message.\n");

    lString->print(lString);

    lString->split(lString, lMap, "\n");
    printf("split: %d\n", lMap->size(lMap));

    lString2->assign(lString2, lMap->get(lMap, 1));
    printf("get: %s\n", lString2->m_data);

    printf("indexOf: %d\n", lString2->indexOf(lString2, "deuxième", 0));
    printf("startsWith: %d\n", lString2->startsWith(lString2, "Voici"));
    printf("endsWith: %d\n", lString2->endsWith(lString2, "message"));

    lString2->substr(lString2, lString3, 3, 3);
    printf("substr: %s\n", lString3->m_data);

    lString2->extract(lString2, lString3, " ", " ");
    printf("extract: %s\n", lString3->m_data);

    smdelete(lMap);
    lString->delete(&lString);
    lString2->delete(&lString2);
    lString3->delete(&lString3);
    lMap->delete(&lMap);
}
//===============================================
static void GTest_runVector(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    printf("%s...\n",  __PRETTY_FUNCTION__);
    GVector* lVector = GVector_new();

    // size - add - get - clear - delete
    printf("size: %d\n", lVector->size(lVector));

    lVector->add(lVector, "un");
    lVector->add(lVector, "deux");
    lVector->add(lVector, "trois");
    printf("size: %d\n", lVector->size(lVector));

    printf("get: %s\n", (char*)lVector->get(lVector, 1));

    lVector->clear(lVector);
    printf("size: %d\n", lVector->size(lVector));

    lVector->delete(&lVector);
}
//===============================================
static void GTest_runLog(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    printf("%s...\n",  __PRETTY_FUNCTION__);

    // addError - addLog - addData - addLogs - print - clear - delete
    GLog* lLog = GLog_new();
    GLog* lLog2 = GLog_new();

    lLog->addError(lLog, "Je suis une erreur.");
    lLog->addLog(lLog, "Je suis une information.");
    lLog->addData(lLog, "Je suis une donnée.");

    // lLog->clear(lLog);

    lLog->print(lLog);

    lLog->loadFromMap(lLog, 2);
    lLog->m_msg = "Je suis une information (2).";
    lLog->loadToMap(lLog, 2);

    lLog2->addLogs(lLog2, lLog);
    lLog2->print(lLog2);

    lLog->delete(&lLog);
    lLog2->delete(&lLog2);
}
//===============================================
static void GTest_runSocket(GTest* _this, int _argc, char** _argv) {
    assert(_this);
    printf("%s...\n",  __PRETTY_FUNCTION__);

    GSocket* lSocket = GSocket_new();

    lSocket->run(lSocket);

    lSocket->delete(&lSocket);
}
//===============================================
