//===============================================
#ifndef _GHostname_
#define _GHostname_
//===============================================
#include "GObject.h"
//===============================================
class GSocket;
//===============================================
class GHostname : public GObject {
public:
    GHostname();
    ~GHostname();
    void onModule(std::string _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
