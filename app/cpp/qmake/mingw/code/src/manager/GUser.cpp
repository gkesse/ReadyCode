//===============================================
#include "GUser.h"
#include "GLog.h"
#include "GFormat.h"
#include "GRequest.h"
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

    // hostname
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
    printf("%s\n", __FUNCTION__);
}
//===============================================
