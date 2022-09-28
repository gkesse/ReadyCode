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
QString GSession::serialize(const QString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "user_id", m_userId);
    return lDom.toStringData();
}
//===============================================
void GSession::deserialize(const QString& _data, const QString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_userId = lDom.getItem(_code, "user_id").toInt();
}
//===============================================
