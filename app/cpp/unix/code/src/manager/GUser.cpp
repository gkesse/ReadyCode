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
void GUser::onModule(GSocket* _client) {
    std::string lMethod = m_req->getMethod();

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
    printf("%s\n", __FUNCTION__);
}
//===============================================
