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
GString GSession::serialize() const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(m_codeName, "user_id", m_userId);
    return lDom.toString();
}
//===============================================
bool GSession::deserialize(const GString& _data) {
    GCode lDom;
    lDom.loadXml(_data);
    m_userId = lDom.getData(m_codeName, "user_id").toInt();
    return true;
}
//===============================================
