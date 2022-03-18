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
    void onModule(GSocket* _client);
    //
    void onModuleUser(GSocket* _client);
};
//==============================================
#endif
//==============================================
