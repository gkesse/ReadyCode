//===============================================
#include "GHostname.h"
#include "GLog.h"
#include "GSocket.h"
//===============================================
GHostname::GHostname() : GModule() {

}
//===============================================
GHostname::GHostname(const std::string& _req) : GModule(_req) {

}
//===============================================
GHostname::~GHostname() {

}
//===============================================
void GHostname::saveHostname(GSocket* _client) {
    if(GLOGI->hasError()) return;
    printf("adresse_ip.....: %s\n", _client->readAddressIp().c_str());
}
//===============================================
