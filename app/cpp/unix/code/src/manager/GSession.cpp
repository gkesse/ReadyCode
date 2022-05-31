//===============================================
#include "GSession.h"
#include "GCode.h"
#include "GString.h"
//===============================================
GSession::GSession() : GObject() {
    m_userId = 0;
}
//===============================================
GSession::~GSession() {

}
//===============================================
std::string GSession::serialize(const std::string& _code) const {
    GCode lReq;
    lReq.createCode(_code, "user_id", m_userId);
    return lReq.toStringCode(_code);
}
//===============================================
void GSession::deserialize(const std::string& _data, const std::string& _code) {
    GCode lReq(_data);
    m_userId = GString(lReq.getItem(_code, "user_id")).toInt();
}
//===============================================
