//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GUser.h"
//===============================================
GMaster::GMaster(QObject* _parent) : GModule(_parent) {

}
//===============================================
GMaster::GMaster(const QString& _req, QObject* _parent) : GModule(_req, _parent) {

}
//===============================================
GMaster::~GMaster() {

}
//===============================================
void GMaster::onModule(QString _req, GSocket* _client) {
    if(GLOGI->hasError()) return;
    QString lModule = getModule();

    // user
    if(lModule == "user") {
        onModuleUser(_req, _client);
    }
    // unknown
    else {
        onModuleUnknown(_req, _client);
    }
}
//===============================================
void GMaster::onModuleUser(QString _req, GSocket* _client) {
    if(GLOGI->hasError()) return;
    GUser lModule(_req);
    lModule.onModule(_req, _client);
}
//===============================================
