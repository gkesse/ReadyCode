//===============================================
#include "GXmlRpcClient.h"
#include "GXmlRpc.h"
//===============================================
GXmlRpcClient::GXmlRpcClient() {

}
//===============================================
GXmlRpcClient::~GXmlRpcClient() {

}
//===============================================
void GXmlRpcClient::run(int argc, char** argv) {
    GXmlRpc lClient;
    lClient.url();
    lClient.call("add", "ii", 7, 5);
    lClient.print();
}
//===============================================
