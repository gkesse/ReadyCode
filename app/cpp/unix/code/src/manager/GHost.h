//===============================================
#ifndef _GHost_
#define _GHost_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GHost : public GModule {
public:
    GHost();
    ~GHost();
    //
    void saveHostname(GSocket* _client);
};
//==============================================
#endif
//==============================================
