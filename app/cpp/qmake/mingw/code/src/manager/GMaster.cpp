//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GFormat.h"
#include "GRequest.h"
#include "GUser.h"
#include "GConsole.h"
#include "GTest.h"
//===============================================
GMaster::GMaster(QObject* _parent) : GModule(_parent) {

}
//===============================================
GMaster::GMaster(const QString& _req, QObject* _parent) : GModule(_req, _parent) {

}
//===============================================
GMaster::~GMaster() {

}
//===============================================
void GMaster::onModule(const QString& _req, GSocket* _client) {
    QString lModule = m_req->getModule();

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
void GMaster::onModuleTest(const QString& _req, GSocket* _client) {
    GTest lModule(_req);
    lModule.onModule(_req, _client);
}
//===============================================
void GMaster::onModuleUser(const QString& _req, GSocket* _client) {
    GUser lModule(_req);
    lModule.onModule(_req, _client);
}
//===============================================
