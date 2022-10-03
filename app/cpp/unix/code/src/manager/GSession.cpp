//===============================================
#include "GSession.h"
#include "GCode.h"
#include "GString.h"
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
    return lDom.toStringCode(_code);
}
//===============================================
void GSession::deserialize(const GString& _data, const GString& _code) {
    GCode lReq;
    lReq.loadXml(_data);
    m_userId = GString(lReq.getData(_code, "user_id")).toInt();
}
//===============================================
