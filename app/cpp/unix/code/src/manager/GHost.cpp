//===============================================
#include "GHost.h"
#include "GLog.h"
#include "GFormat.h"
#include "GSocket.h"
//===============================================
GHost::GHost() : GModule() {

}
//===============================================
GHost::GHost(const std::string& _req) : GModule(_req) {

}
//===============================================
GHost::~GHost() {

}
//===============================================
void GHost::saveHostname(GSocket* _client) {
    GLOGT(eGMSG, "client_ip.....: %s", _client->readAddressIp().c_str());
}
//===============================================
