//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GHostname.h"
//===============================================
GMaster::GMaster() : GObject() {

}
//===============================================
GMaster::~GMaster() {

}
//===============================================
void GMaster::onModule(std::string _req, GSocket* _client) {
    GXml lReq;
    lReq.createXPath(_req);
    std::string lModule = lReq.getModule();

    // hostname
    if(lModule == "hostname") {
        onModuleHostname(_req, _client);
    }
    // unknown
    else {
        onUnknown(_req, _client);
    }
}
//===============================================
void GMaster::onUnknown(std::string _req, GSocket* _client) {

}
//===============================================
void GMaster::onModuleHostname(std::string _req, GSocket* _client) {
    GHostname lModule;
    lModule.onModule(_req, _client);
}
//===============================================
