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
    lParent->deserialize(lParent, _data->m_data);
    if(!strcmp(lMgr->m_module, "logs")) {

    }
}
//===============================================
static void GServer_send(GServer* _this, GSocket* _socket) {
    assert(_this);
    _socket->send(_socket, "Bonjour cher client. J'ai bien recu ton message.");
}
//===============================================
