//===============================================
#ifndef _GMaster_
#define _GMaster_
//===============================================
#include "GObject.h"
//===============================================
class GSocket;
//===============================================
class GMaster : public GObject {
public:
    GMaster();
    ~GMaster();
    void onModule(std::string _req, GSocket* _client);
    void onUnknown(std::string _req, GSocket* _client);
    //
    void onModuleHostname(std::string _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
