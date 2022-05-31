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
#include "GMaj.h"
//===============================================
GMaster::GMaster() : GModule() {
    m_validateXml = false;
    m_validateReq = true;
}
//===============================================
GMaster::~GMaster() {

}
//===============================================
std::string GMaster::serialize(const std::string& _code) const {
    GCode lReq;
    lReq.createCode(_code, "module", m_module);
    return lReq.toStringCode(_code);
}
//===============================================
void GMaster::deserialize(const std::string& _data, const std::string& _code) {
    GModule::deserialize(_data);
    GCode lReq(_data);
    m_module = lReq.getItem(_code, "module");
    m_method = lReq.getItem(_code, "method");
}
//===============================================
void GMaster::onModule(GSocket* _client) {
    validateXmlRequest(_client->toReq());
    deserialize(_client->toReq());

    //===============================================
    // valid
    //===============================================
    if(!m_validateXml) {
        onXmlInvalid(_client);
    }
    else if(!m_validateReq) {
        onReqInvalid(_client);
    }
    else {
        //===============================================
        // module
        //===============================================
        if(m_module == "test") {
            onModuleTest(_client);
        }
        else if(m_module == "user") {
            onModuleUser(_client);
        }
        else if(m_module == "req") {
            onModuleReq(_client);
        }
        else if(m_module == "maj") {
            onModuleMaj(_client);
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
        GRequest().onSaveRequest(_client);
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
void GMaster::onModuleReq(GSocket* _client) {
    GRequest().onModule(_client);
}
//===============================================
void GMaster::onModuleMaj(GSocket* _client) {
    GMaj().onModule(_client);
}
//===============================================
void GMaster::validateXmlRequest(const std::string& _data) {
    GCode lReq(_data);
    m_validateXml = lReq.isValidXml();
    m_validateReq = lReq.isValidReq();
}
//===============================================
