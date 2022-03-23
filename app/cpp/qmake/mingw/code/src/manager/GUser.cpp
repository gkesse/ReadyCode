//===============================================
#include "GUser.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GUser::GUser(QObject* _parent) : GModule(_parent) {

}
//===============================================
GUser::GUser(const QString& _req, QObject* _parent) : GModule(_req, _parent) {

}
//===============================================
GUser::~GUser() {

}
//===============================================
void GUser::onModule(GSocket* _client) {
    QString lMethod = m_req->getMethod();

    // method
    if(lMethod == "save_user") {
        onSaveUser(_client);
    }
    // unknown
    else {
        onMethodUnknown(_client);
    }
}
//===============================================
void GUser::onSaveUser(GSocket* _client) {
    GSocket* lClient = _client;
    QSharedPointer<GCode>& lRes = lClient->getResponse();
    lRes->createCode("user", "firstname", "Gerard");
    lRes->createCode("user", "lastname", "KESSE");
    GERROR(QString("Erreur identifiant"));
    GERROR(QString("Erreur mot de passe"));
}
//===============================================
