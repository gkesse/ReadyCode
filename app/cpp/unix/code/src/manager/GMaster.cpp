//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GUser.h"
#include "GSocket.h"
#include "GCode.h"
#include "GTest.h"
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
void GMaster::onModule(const std::string& _req, GSocket* _client) {
    std::string lModule = m_req->getModule();

    // module
    if(lModule == "test") {
        onModuleTest(_req, _client);
    }
    else if(lModule == "user") {
        onModuleUser(_req, _client);
    }
    // unknown
    else {
        onModuleUnknown(_req, _client);
    }
}
//===============================================
void GMaster::onModuleTest(const std::string& _req, GSocket* _client) {
    GTest lModule(_req);
    lModule.onModule(_req, _client);
}
//===============================================
void GMaster::onModuleUser(const std::string& _req, GSocket* _client) {
    GUser lModule(_req);
    lModule.onModule(_req, _client);
}
//===============================================
