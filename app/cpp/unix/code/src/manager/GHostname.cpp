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
void GHostname::onModule(const std::string& _req, GSocket* _client) {
    if(GLOGI->hasError()) return;
    std::string lMethod = getMethod();

    if(lMethod == "save_hostname") {
        onSaveHostname(_req, _client);
    }
    else {
        onMethodUnknown(_req, _client);
    }
}
//===============================================
void GHostname::onSaveHostname(const std::string& _req, GSocket* _client) {
    printf("%s\n", __FUNCTION__);
    if(GLOGI->hasError()) return;
    printf("adresse_ip.....;%d\n", _client->readPort());
}
//===============================================
