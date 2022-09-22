//===============================================
#include "GHost.h"
#include "GLog.h"
#include "GSocket.h"
//===============================================
GHost::GHost() : GModule() {

}
//===============================================
GHost::~GHost() {

}
//===============================================
void GHost::saveHostname(GSocket* _client) {
    GLOGT(eGMSG, "client_ip....: (%s)\n", _client->readAddressIp().c_str());
}
//===============================================
