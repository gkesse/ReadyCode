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
    void sendResponse(GSocket* _socket);
    void run(const GString& _data);
    void runFacade(const GString& _data);
    void runMaster(const GString& _data);
    void runCalculator(const GString& _data);
};
//===============================================
#endif
//===============================================
