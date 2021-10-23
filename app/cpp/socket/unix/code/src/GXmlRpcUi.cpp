//===============================================
#include "GXmlRpcUi.h"
#include "GXmlRpcServer.h"
#include "GXmlRpcClient.h"
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
    printf("[xmlrpc] process par defaut\n");
}
//===============================================
