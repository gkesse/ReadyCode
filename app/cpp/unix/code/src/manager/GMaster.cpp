//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GXml.h"
#include "GUser.h"
#include "GSocket.h"
#include "GCode.h"
#include "GTest.h"
#include "GRequest.h"
#include "GMaj.h"
#include "GMd5.h"
#include "GManager.h"
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
bool GMaster::onModule(GSocket* _client) {
    if(!isValidXml(_client->toReq())) return false;
    deserialize(_client->toReq());
    if(!isValidReq()) return false;
    //===============================================
    if(m_module == "") {
        onModuleNone(_client);
        return false;
    }
    else if(m_method == "") {
        onMethodNone(_client);
        return false;
    }
    //===============================================
    // module
    //===============================================
    else if(m_module == "test") {
        onTest(_client);
    }
    else if(m_module == "user") {
        onUser(_client);
    }
    else if(m_module == "req") {
        onReq(_client);
    }
    else if(m_module == "maj") {
        onMaj(_client);
    }
    else if(m_module == "md5") {
        onMd5(_client);
    }
    else if(m_module == "manager") {
        onManager(_client);
    }
    //===============================================
    // unknown
    //===============================================
    else {
        onModuleUnknown(_client);
        return false;
    }
    //===============================================
    // end
    //===============================================
    GRequest lRequest;
    lRequest.onSaveRequest(_client);
    //===============================================
    return true;
}
//===============================================
void GMaster::onTest(GSocket* _client) {
    GTest lTest;
    lTest.onModule(_client);
}
//===============================================
void GMaster::onUser(GSocket* _client) {
    GUser lUser;
    lUser.onModule(_client);
}
//===============================================
void GMaster::onReq(GSocket* _client) {
    GRequest lRequest;
    lRequest.onModule(_client);
}
//===============================================
void GMaster::onMaj(GSocket* _client) {
    GMaj lMaj;
    lMaj.onModule(_client);
}
//===============================================
void GMaster::onMd5(GSocket* _client) {
    GMd5 lMd5;
    lMd5.onModule(_client);
}
//===============================================
void GMaster::onManager(GSocket* _client) {
    GManager lManager;
    lManager.onModule(_client);
}
//===============================================
bool GMaster::isValidXml(const std::string& _data) {
    std::string lData = GString(_data).trimData();
    if(lData == "") return false;
    GCode lReq;
    lReq.loadXml(_data);
    bool lValidXml = lReq.isValidXml();
    if(!lValidXml) {GERROR_ADD(eGERR, "Erreur le XML est invalide."); return false;}
    return true;
}
//===============================================
bool GMaster::isValidReq() {
    bool lValidReq = true;
    lValidReq &= (m_module != "");
    lValidReq &= (m_method != "");
    if(!lValidReq) {GERROR_ADD(eGERR, "Erreur la requete est invalide."); return false;}
    return true;
}
//===============================================
