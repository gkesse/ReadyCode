//===============================================
#include "GServer.h"
//===============================================
#define GServer_BUFFER_SIZE 10
//===============================================
static void GServer_delete(GServer* _this);
static GString* GServer_toString(GServer* _this);
static void GServer_run(GServer* _this, const char* _module, const char* _method, const char* _data);
static void GServer_runCalculator(GServer* _this, const char* _method, const char* _data);
//===============================================
GServer* GServer_new() {
    GServer* lObj = (GServer*)malloc(sizeof(GServer));
    lObj->m_obj = GObject_new();

    lObj->delete = GServer_delete;
    lObj->toString = GServer_toString;
    lObj->run = GServer_run;
    lObj->runCalculator = GServer_runCalculator;
    return lObj;
}
//===============================================
static void GServer_delete(GServer* _this) {
    assert(_this);
    _this->m_obj->delete(_this->m_obj);
    free(_this);
}
//===============================================
static GString* GServer_toString(GServer* _this) {
    assert(_this);
    GCode* lResp = _this->m_obj->m_resp;
    GLog* lLog = _this->m_obj->m_logs;
    GString* lData = GString_new();
    lData->assign(lData, lLog->serialize(lLog));
    lResp->loadData(lResp, lData->m_data);
    lData->delete(lData);
    return lResp->m_dom->toString(lResp->m_dom);
}
//===============================================
static void GServer_run(GServer* _this, const char* _module, const char* _method, const char* _data) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;

    if(!strcmp(_module, "")) {
        lLog->addError(lLog, "Le module est obligatoire.");
    }
    else if(!strcmp(_module, "calculator")) {
        _this->runCalculator(_this, _method, _data);
    }
    else {
        lLog->addError(lLog, "Le module est inconnu.");
    }
}
//===============================================
static void GServer_runCalculator(GServer* _this, const char* _method, const char* _data) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;
    lLog->addError(lLog, "Le module calculator a été trouvé.");
}
//===============================================
