//===============================================
#include "GUser.h"
#include "GCode.h"
#include "GSocket.h"
#include "GLog.h"
//===============================================
GUser* GUser::m_instance = 0;
//===============================================
GUser::GUser(QObject* _parent) : GObject(_parent) {
    m_pseudo = "root";
}
//===============================================
GUser::~GUser() {

}
//===============================================
GUser* GUser::Instance() {
    if(m_instance == 0) {
        m_instance = new GUser;
    }
    return m_instance;
}
//===============================================
QString GUser::getPseudo() const {
    return m_pseudo;
}
//===============================================
bool GUser::hasUser(const QString& _username) const {
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("user", "has_user");
    lReq.addParam("username", _username);
    GLOGT(eGMSG, lReq.toString());
    QString lResponse = lClient.callServer(lReq.toString());
    GERROR_LOAD(eGERR, lResponse);
    return !GLOGI->hasErrors();
}
//===============================================
bool GUser::hasUser(const QString& _username, const QString& _password) const {
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("user", "has_user_password");
    lReq.addParam("username", _username);
    lReq.addParam("password", _password);
    GLOGT(eGMSG, lReq.toString());
    QString lResponse = lClient.callServer(lReq.toString());
    GERROR_LOAD(eGERR, lResponse);
    return !GLOGI->hasErrors();
}
//===============================================
