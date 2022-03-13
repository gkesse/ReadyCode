//===============================================
#ifndef _GUser_
#define _GUser_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GUser : public GModule {
public:
    GUser();
    GUser(const std::string& _req);
    ~GUser();
    //
    void onModule(std::string _req, GSocket* _client);
    void onSaveUser(std::string _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
