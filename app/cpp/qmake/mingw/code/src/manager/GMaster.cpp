//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GCode.h"
#include "GUser.h"
#include "GTest.h"
#include "GSocket.h"
//===============================================
GMaster::GMaster(QObject* _parent) : GModule(_parent) {

}
//===============================================
GMaster::~GMaster() {

}
//===============================================
void GMaster::onModule(GSocket* _client) {
    QString lModule = _client->getReq()->getModule();
    //===============================================
    // module
    //===============================================
    if(lModule == "test") {
        onModuleTest(_client);
    }
    //===============================================
    // unknown
    //===============================================
    else {
        onModuleUnknown(_client);
    }
}
//===============================================
void GMaster::onModuleTest(GSocket* _client) {
    GTest().onModule(_client);
}
//===============================================
