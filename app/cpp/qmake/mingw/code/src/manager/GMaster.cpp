//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
#include "GUser.h"
#include "GConsole.h"
#include "GTest.h"
#include "GSocket.h"
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
void GMaster::onModule(GSocket* _client) {
    QString lModule = m_req->getModule();

    // module
    if(lModule == "test") {
        onModuleTest(_client);
    }
    else if(lModule == "user") {
        onModuleUser(_client);
    }
    // unknown
    else {
        onModuleUnknown(_client);
    }
}
//===============================================
void GMaster::onModuleTest(GSocket* _client) {
    GTest lModule(_client->getRequest());
    lModule.onModule(_client);
}
//===============================================
void GMaster::onModuleUser(GSocket* _client) {
    GUser lModule(_client->getRequest());
    lModule.onModule(_client);
}
//===============================================
