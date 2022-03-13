//===============================================
#ifndef _GHostname_
#define _GHostname_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GHostname : public GModule {
public:
    GHostname();
    GHostname(const std::string& _req);
    ~GHostname();
    //
    void saveHostname(GSocket* _client);
};
//==============================================
#endif
//==============================================
