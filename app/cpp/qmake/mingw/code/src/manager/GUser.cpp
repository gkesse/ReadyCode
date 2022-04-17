//===============================================
#include "GUser.h"
#include "GCode.h"
#include "GSocket.h"
#include "GLog.h"
//===============================================
GUser::GUser(QObject* _parent) : GObject(_parent) {

}
//===============================================
GUser::~GUser() {

}
//===============================================
bool GUser::hasUser(const QString& _username) const {
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("user", "has_user");
    lReq.addParameter("username", _username);
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
    lReq.addParameter("username", _username);
    lReq.addParameter("password", _password);
    GLOGT(eGMSG, lReq.toString());
    QString lResponse = lClient.callServer(lReq.toString());
    GERROR_LOAD(eGERR, lResponse);
    return !GLOGI->hasErrors();
}
//===============================================
