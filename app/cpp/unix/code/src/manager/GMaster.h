//===============================================
#ifndef _GMaster_
#define _GMaster_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GMaster : public GModule {
public:
    GMaster();
    GMaster(const std::string& _req);
    ~GMaster();
    //
    void onModule(const std::string& _req, GSocket* _client);
    //
    void onModuleTest(const std::string& _req, GSocket* _client);
    void onModuleUser(const std::string& _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
