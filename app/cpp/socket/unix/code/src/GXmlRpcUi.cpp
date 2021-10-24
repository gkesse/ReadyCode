//===============================================
#include "GXmlRpcUi.h"
#include "GXmlRpc.h"
#include "GXmlRpcM.h"
//===============================================
GXmlRpcUi::GXmlRpcUi() {

}
//===============================================
GXmlRpcUi::~GXmlRpcUi() {

}
//===============================================
GXmlRpcUi* GXmlRpcUi::Create(const std::string& key) {
    if(key == "default") {return new GXmlRpcUi;}
    return new GXmlRpcUi;
}
//===============================================
void GXmlRpcUi::run(int argc, char** argv) {
	GXmlRpcM* lAdd;
    GXmlRpc lServer;
    lServer.name("add");
    lServer.method(lAdd);
    lServer.registry();
    lServer.server();
    lServer.run();
}
//===============================================
