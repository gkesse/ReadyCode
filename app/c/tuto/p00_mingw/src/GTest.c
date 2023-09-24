//===============================================
#include "GTest.h"
#include "GVector.h"
#include "GLog.h"
//===============================================
static void GTest_delete(GTest** _this);
static void GTest_run(GTest* _this, int _argc, char** _argv);
static void GTest_runVector(GTest* _this, int _argc, char** _argv);
static void GTest_runLog(GTest* _this, int _argc, char** _argv);
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
    else if(!strcmp(lModule, "vector")) {
        GTest_runVector(_this, _argc, _argv);
    }
    else if(!strcmp(lModule, "log")) {
        GTest_runLog(_this, _argc, _argv);
    }
    else {
        lLog->addError(lLog, "Le module est inconnu.");
    }
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
