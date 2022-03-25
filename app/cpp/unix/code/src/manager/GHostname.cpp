//===============================================
#include "GHostname.h"
#include "GLog.h"
#include "GFormat.h"
#include "GSocket.h"
#include "GConsole.h"
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
    console("=====>");
    consoles("client_ip.....: %s", _client->readAddressIp().c_str());
}
//===============================================
