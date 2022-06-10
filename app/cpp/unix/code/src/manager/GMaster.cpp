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
#include "GString.h"
//===============================================
GMaster::GMaster() : GModule() {
    m_validateXml = false;
    m_validateReq = false;
}
//===============================================
GMaster::~GMaster() {

}
//===============================================
std::string GMaster::serialize(const std::string& _code) const {
    return "";
}
//===============================================
void GMaster::deserialize(const std::string& _data, const std::string& _code) {
    GModule::deserialize(_data);
}
//===============================================
void GMaster::onModule(GSocket* _client) {
    if(isValidXml(_client->toReq())) return;
    deserialize(_client->toReq());
    if(isValidReq()) return;
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
    GRequest lRequest;
    lRequest.onSaveRequest(_client);
    //===============================================
}
//===============================================
void GMaster::onModuleTest(GSocket* _client) {
    GTest lTest;
    lTest.onModule(_client);
}
//===============================================
void GMaster::onModuleUser(GSocket* _client) {
    GUser lUser;
    lUser.onModule(_client);
}
//===============================================
void GMaster::onModuleReq(GSocket* _client) {
    GRequest lRequest;
    lRequest.onModule(_client);
}
//===============================================
void GMaster::onModuleMaj(GSocket* _client) {
    GMaj lMaj;
    lMaj.onModule(_client);
}
//===============================================
bool GMaster::isValidXml(const std::string& _data) {
    std::string lData = GString(_data).trimData();
    if(lData == "") return false;
    GCode lReq;
    lReq.loadXml(_data);
    bool lValidXml = lReq.isValidXml();
    if(!lValidXml) {GERROR(eGERR, "Erreur le XML est invalide."); return false;}
    return true;
}
//===============================================
bool GMaster::isValidReq() {
    bool lValidReq = true;
    lValidReq &= (m_module != "");
    lValidReq &= (m_method != "");
    if(!lValidReq) {GERROR(eGERR, "Erreur la requete est invalide."); return false;}
    return true;
}
//===============================================
