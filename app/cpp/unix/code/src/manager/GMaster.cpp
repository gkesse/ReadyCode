//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GUser.h"
#include "GSocket.h"
#include "GCode.h"
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
    std::string lModule = m_req->getModule();

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
void GMaster::onModuleUser(GSocket* _client) {
    GUser lModule(_client->getRequest());
    lModule.onModule(_client);
}
//===============================================
