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
void GHostname::saveHostname(const std::string& _req, GSocket* _client) {
    printf("adresse_ip.....: %s\n", _client->readAddressIp().c_str());
}
//===============================================
