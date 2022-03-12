//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GObject.h"
//===============================================
class GSocket;
//===============================================
class GModule : public GObject {
public:
    GModule();
    ~GModule();
    void onModule(std::string _req, GSocket* _client);
    void onUnknown(std::string _req, GSocket* _client);
    //
    void onModuleHostname(std::string _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
