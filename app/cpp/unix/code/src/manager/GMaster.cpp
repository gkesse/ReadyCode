//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GUser.h"
#include "GSocket.h"
#include "GCode.h"
#include "GTest.h"
#include "GRequest.h"
//===============================================
GMaster::GMaster() : GModule() {

}
//===============================================
GMaster::~GMaster() {

}
//===============================================
void GMaster::onModule(GSocket* _client) {
    bool lValidXml = _client->getReq()->isValidXml();
    bool lValidReq = _client->getReq()->isValidReq();
    std::string lModule = _client->getReq()->getModule();
    std::string lMethod = _client->getReq()->getMethod();

    //===============================================
    // valid
    //===============================================
    if(!lValidXml) {
        onXmlInvalid(_client);
    }
    else if(!lValidReq) {
        onReqInvalid(_client);
    }
    else {
        //===============================================
        // module
        //===============================================
        if(lModule == "test") {
            onModuleTest(_client);
        }
        else if(lModule == "user") {
            onModuleUser(_client);
        }
        //===============================================
        // unknown
        //===============================================
        else {
            onModuleUnknown(_client);
        }
        //===============================================
        // end
        //===============================================
        GRequest lReq(_client->getReq()->toString());
        lReq.saveData();
        //===============================================
    }
}
//===============================================
void GMaster::onModuleTest(GSocket* _client) {
    GTest().onModule(_client);
}
//===============================================
void GMaster::onModuleUser(GSocket* _client) {
    GUser().onModule(_client);
}
//===============================================
