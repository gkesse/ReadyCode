//===============================================
#include "GServer.h"
#include "GSocket.h"
#include "GManager.h"
#include "GCalculator.h"
//===============================================
#define GServer_BUFFER_SIZE 10
//===============================================
static void GServer_delete(GServer* _this);
static void GServer_send(GServer* _this, GSocket* _socket);
static void GServer_run(GServer* _this, const char* _data);
static void GServer_runCalculator(GServer* _this, const char* _data);
//===============================================
GServer* GServer_new() {
    GServer* lObj = (GServer*)malloc(sizeof(GServer));
    lObj->m_mgr = GManager_new();
    lObj->m_obj = GObject_new();

    lObj->delete = GServer_delete;
    lObj->send = GServer_send;
    lObj->run = GServer_run;
    lObj->runCalculator = GServer_runCalculator;
    return lObj;
}
//===============================================
static void GServer_delete(GServer* _this) {
    assert(_this);
    _this->m_mgr->delete(_this->m_mgr);
    _this->m_obj->delete(_this->m_obj);
    free(_this);
}
//===============================================
static void GServer_send(GServer* _this, GSocket* _socket) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;
    GCode* lResp = _this->m_obj->m_resp;
    GXml* lDom = _this->m_obj->m_resp->m_dom;
    GString* lData = GString_new();

    lData->assign(lData, lLog->serialize(lLog));
    lResp->loadData(lResp, lData->m_data);
    lData->assign(lData, lDom->toString(lDom));
    _socket->send(_socket, lData->m_data);

    lData->delete(lData);
}
//===============================================
static void GServer_run(GServer* _this, const char* _data) {
    assert(_this);
    GManager* lMgr = _this->m_mgr;
    GLog* lLog = _this->m_obj->m_logs;
    lMgr->m_obj->deserialize(lMgr->m_obj, _data);

    if(!strcmp(lMgr->m_module, "")) {
        lLog->addError(lLog, "Le module est obligatoire.");
    }
    else if(!strcmp(lMgr->m_module, "calculator")) {
        _this->runCalculator(_this, _data);
    }
    else {
        lLog->addError(lLog, "Le module est inconnu.");
    }
}
//===============================================
static void GServer_runCalculator(GServer* _this, const char* _data) {
    assert(_this);
    GCalculator* lObjC = GCalculator_new();
    GObject* lRespC = lObjC->m_obj;
    GLog* lLogC = lObjC->m_obj->m_logs;
    GCode* lRespT = _this->m_obj->m_resp;
    GLog* lLogT = _this->m_obj->m_logs;

    lObjC->run(lObjC, _data);
    lLogT->addLogs(lLogT, lLogC);
    lRespT->loadData(lRespT, lRespC->serialize(lRespC)->m_data);

    lObjC->delete(lObjC);
}
//===============================================
