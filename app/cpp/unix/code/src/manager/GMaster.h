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
    void onModule(std::string _req, GSocket* _client);
    //
    void onModuleHostname(std::string _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
