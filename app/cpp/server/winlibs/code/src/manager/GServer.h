//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GObject.h"
//===============================================
class GSocket;
//===============================================
class GServer : public GObject {
public:
    GServer();
    ~GServer();
    void run(const GString& _data);
    void sendResponse(GSocket* _socket);
};
//===============================================
#endif
//===============================================
