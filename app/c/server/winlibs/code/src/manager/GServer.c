//===============================================
#include "GServer.h"
#include "GSocket.h"
#include "GManager.h"
//===============================================
#define GServer_BUFFER_SIZE 10
//===============================================
static void GServer_delete(GServer* _this);
static void GServer_run(GServer* _this, GString* _data);
static void GServer_send(GServer* _this, GSocket* _socket);
//===============================================
GServer* GServer_new() {
    GServer* lObj = (GServer*)malloc(sizeof(GServer));
    lObj->m_mgr = GManager_new();

    lObj->delete = GServer_delete;
    lObj->run = GServer_run;
    lObj->send = GServer_send;
    return lObj;
}
//===============================================
static void GServer_delete(GServer* _this) {
    assert(_this);
    _this->m_mgr->delete(_this->m_mgr);
    free(_this);
}
//===============================================
static void GServer_run(GServer* _this, GString* _data) {
    assert(_this);
    GManager* lMgr = _this->m_mgr;
    GObject* lParent = _this->m_mgr->m_parent;
    GLog* lLog = _this->m_mgr->m_parent->m_logs;
    lParent->deserialize(lParent, _data->m_data);

    if(!strcmp(lMgr->m_module, "")) {
        lLog->addError(lLog, "Le module est obligatoire.");
    }
    else if(!strcmp(lMgr->m_module, "logs")) {
        lLog->addLog(lLog, "Le module a été trouvé.");
    }
    else {
        lLog->addError(lLog, "Le module est inconnu.");
    }
}
//===============================================
static void GServer_send(GServer* _this, GSocket* _socket) {
    assert(_this);
    GLog* lLog = _this->m_mgr->m_parent->m_logs;
    GString* lData = GString_new();
    lData->assign(lData, lLog->serialize(lLog));
    _socket->send(_socket, lData->m_data);
    lData->delete(lData);
}
//===============================================
