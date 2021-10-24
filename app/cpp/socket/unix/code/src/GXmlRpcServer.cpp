//===============================================
#include "GXmlRpcServer.h"
#include "GXmlRpc.h"
//===============================================
GXmlRpcServer::GXmlRpcServer() {

}
//===============================================
GXmlRpcServer::~GXmlRpcServer() {

}
//===============================================
void GXmlRpcServer::run(int argc, char** argv) {
    GXmlRpcM* lAdd = new GXmlRpcM;
    lAdd->signature("i:ii");
    lAdd->help("Ajouter deux entiers");
    lAdd->onExecute(onAdd);

    GXmlRpc lServer;
    lServer.addMethod("add", lAdd);
    lServer.server();
    lServer.start();
    lServer.run();
}
//===============================================
void GXmlRpcServer::onAdd(GXmlRpcM::pList _params, GXmlRpcM::pValue _value) {
    GXmlRpc lServer;
    lServer.onAdd(_params, _value);
}
//===============================================
