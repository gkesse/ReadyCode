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
bool GUser::existUsername(const QString& _username) const {
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("user", "exist_username");
    GLOGT(eGMSG, lReq.toString());
    QString lResponse = lClient.callServer(lReq.toString());
    GLOGI->loadErrors(lResponse);
    return GLOGI->hasErrors();
}
//===============================================
