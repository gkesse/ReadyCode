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
    void onModule(const std::string& _req, GSocket* _client);
    void onSaveHostname(const std::string& _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
