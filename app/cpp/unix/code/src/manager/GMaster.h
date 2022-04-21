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
    ~GMaster();
    //
    void onModule(GSocket* _client);
    //
    void onModuleTest(GSocket* _client);
    void onModuleUser(GSocket* _client);
    void onModuleReq(GSocket* _client);
};
//==============================================
#endif
//==============================================
