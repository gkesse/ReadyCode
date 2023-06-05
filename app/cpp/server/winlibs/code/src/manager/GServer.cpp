//===============================================
#include "GServer.h"
#include "GSocket.h"
//===============================================
GServer::GServer()
: GObject() {

}
//===============================================
GServer::~GServer() {

}
//===============================================
void GServer::run(const GString& _data) {
    _data.print();
}
//===============================================
void GServer::sendResponse(GSocket* _socket) {
    GString lData = "OK...";
    _socket->sendData(lData);
}
//===============================================
