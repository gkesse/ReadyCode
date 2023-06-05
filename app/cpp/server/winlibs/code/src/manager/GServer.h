//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GManager.h"
//===============================================
class GSocket;
//===============================================
class GServer : public GManager {
public:
    GServer();
    ~GServer();
    void run(const GString& _data);
    void sendResponse(GSocket* _socket);
};
//===============================================
#endif
//===============================================
