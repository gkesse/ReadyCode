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
	lClient.name("add");
	lClient.call();
}
//===============================================
