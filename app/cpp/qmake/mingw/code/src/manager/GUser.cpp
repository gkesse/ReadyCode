//===============================================
#include "GUser.h"
#include "GLog.h"
#include "GFormat.h"
#include "GRequest.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GUser::GUser() : GModule() {

}
//===============================================
GUser::GUser(const QString& _req) : GModule(_req) {

}
//===============================================
GUser::~GUser() {

}
//===============================================
void GUser::onModule(QString _req, GSocket* _client) {
    QString lMethod = m_req->getMethod();

    // method
    if(lMethod == "save_user") {
        onSaveUser(_req, _client);
    }
    // unknown
    else {
        onMethodUnknown(_req, _client);
    }
}
//===============================================
void GUser::onSaveUser(QString _req, GSocket* _client) {
    GSocket* lClient = _client;
    QSharedPointer<GCode>& lRes = lClient->getResponse();
    lRes->createCode("user", "firstname", "Gerard");
    lRes->createCode("user", "lastname", "KESSE");
    GLOG(QString("Erreur identifiant"));
    GLOG(QString("Erreur mot de passe"));
}
//===============================================
