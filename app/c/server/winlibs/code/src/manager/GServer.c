//===============================================
#include "GServer.h"
#include "GSocket.h"
//===============================================
#define GServer_BUFFER_SIZE 10
//===============================================
static void GServer_delete(GServer* _this);
static void GServer_run(GServer* _this, GString* _data);
static void GServer_send(GServer* _this, GSocket* _socket);
//===============================================
GServer* GServer_new() {
    GServer* lObj = (GServer*)malloc(sizeof(GServer));
    lObj->m_parent = GObject_new();
    lObj->delete = GServer_delete;
    lObj->run = GServer_run;
    lObj->send = GServer_send;
    return lObj;
}
//===============================================
static void GServer_delete(GServer* _this) {
    assert(_this);
    _this->m_parent->delete(_this->m_parent);
    free(_this);
}
//===============================================
static void GServer_run(GServer* _this, GString* _data) {
    assert(_this);
    _data->print(_data);
}
//===============================================
static void GServer_send(GServer* _this, GSocket* _socket) {
    assert(_this);
    _socket->send(_socket, "Bonjour cher client. J'ai bien recu ton message.");
}
//===============================================
