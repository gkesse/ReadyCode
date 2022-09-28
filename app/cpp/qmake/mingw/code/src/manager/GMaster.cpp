//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GCode.h"
#include "GUser.h"
#include "GTest.h"
#include "GSocket.h"
//===============================================
GMaster::GMaster()
: GModule() {
    m_validateXml = false;
    m_validateReq = false;
}
//===============================================
GMaster::~GMaster() {

}
//===============================================
QString GMaster::serialize(const QString& _code) const {
    return "";
}
//===============================================
void GMaster::deserialize(const QString& _data, const QString& _code) {
    GModule::deserialize(_data);
}
//===============================================
bool GMaster::onModule(GSocket* _client) {
    if(!isValidXml(_client->toReq())) return false;
    deserialize(_client->toReq());
    if(!isValidReq()) return false;
    //
    if(m_module == "") {
        onModuleNone(_client);
        return false;
    }
    else if(m_method == "") {
        onMethodNone(_client);
        return false;
    }
    else if(m_module == "test") {
        onTest(_client);
    }
    else {
        onModuleUnknown(_client);
        return false;
    }
    //
    return true;
}
//===============================================
void GMaster::onTest(GSocket* _client) {
    GTest lTest;
    lTest.onModule(_client);
}
//===============================================
bool GMaster::isValidXml(const QString& _data) {
    QString lData = _data.trimmed();
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
