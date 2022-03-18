//===============================================
#include "GUser.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
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
void GUser::onModule(const std::string& _req, GSocket* _client) {
    std::string lMethod = m_req->getMethod();

    // method
    if(lMethod == "save_user") {
        onSaveUser(_req, _client);
    }
    // unknown
    else {
        onModuleUnknown(_req, _client);
    }
}
//===============================================
void GUser::onSaveUser(const std::string& _req, GSocket* _client) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
