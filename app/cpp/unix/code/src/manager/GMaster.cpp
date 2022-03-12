//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GHostname.h"
//===============================================
GMaster::GMaster() : GModule() {

}
//===============================================
GMaster::GMaster(const std::string& _req) : GModule(_req) {

}
//===============================================
GMaster::~GMaster() {

}
//===============================================
void GMaster::onModule(std::string _req, GSocket* _client) {
    if(GLOGI->hasError()) return;
    std::string lModule = getModule();

    // hostname
    if(lModule == "hostname") {
        onModuleHostname(_req, _client);
    }
    // unknown
    else {
        onModuleUnknown(_req, _client);
    }
}
//===============================================
void GMaster::onModuleHostname(std::string _req, GSocket* _client) {
    if(GLOGI->hasError()) return;
    GHostname lModule(_req);
    lModule.onModule(_req, _client);
}
//===============================================
