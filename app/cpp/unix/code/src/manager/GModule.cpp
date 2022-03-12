//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GHostname.h"
//===============================================
GModule::GModule() : GObject() {

}
//===============================================
GModule::~GModule() {

}
//===============================================
void GModule::onModule(std::string _req, GSocket* _client) {
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
void GModule::onUnknown(std::string _req, GSocket* _client) {

}
//===============================================
void GModule::onModuleHostname(std::string _req, GSocket* _client) {
    GHostname lModule;
    lModule.onModule(_req, _client);
}
//===============================================
