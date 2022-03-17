//===============================================
#include "GUser.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
//===============================================
GUser::GUser() : GModule() {

}
//===============================================
GUser::GUser(const std::string& _req) : GModule(_req) {

}
//===============================================
GUser::~GUser() {

}
//===============================================
void GUser::onModule(std::string _req, GSocket* _client) {
    std::string lMethod = getMethod();

    // hostname
    if(lMethod == "save_user") {
        onSaveUser(_req, _client);
    }
    // unknown
    else {
        onModuleUnknown(_req, _client);
    }
}
//===============================================
void GUser::onSaveUser(std::string _req, GSocket* _client) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
