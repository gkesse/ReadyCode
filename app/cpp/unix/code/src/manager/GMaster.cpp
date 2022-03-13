//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GUser.h"
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
    if(lModule == "user") {
        onModuleUser(_req, _client);
    }
    // unknown
    else {
        onModuleUnknown(_req, _client);
    }
}
//===============================================
void GMaster::onModuleUser(std::string _req, GSocket* _client) {
    if(GLOGI->hasError()) return;
    GUser lModule(_req);
    lModule.onModule(_req, _client);
}
//===============================================
