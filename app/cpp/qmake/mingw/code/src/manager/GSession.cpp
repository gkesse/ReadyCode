//===============================================
#include "GSession.h"
#include "GCode.h"
//===============================================
GSession::GSession()
: GObject() {
    m_userId = 0;
}
//===============================================
GSession::~GSession() {

}
//===============================================
GString GSession::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "user_id", m_userId);
    return lDom.toString();
}
//===============================================
bool GSession::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_userId = lDom.getData(_code, "user_id").toInt();
    return true;
}
//===============================================
