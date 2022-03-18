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
void GMaster::onModule(GSocket* _client) {
    std::string lModule = getModule();

    // module
    if(lModule == "user") {
        onModuleUser(_client);
    }
    // unknown
    else {
        onModuleUnknown(_client);
    }
}
//===============================================
void GMaster::onModuleUser(std::string _req, GSocket* _client) {
    GUser lModule(_req);
    lModule.onModule(_req, _client);
}
//===============================================
