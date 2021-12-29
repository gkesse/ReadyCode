//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
#define GMGR
//===============================================
class GManager {
public:
    GManager();
    ~GManager();
    void callServer(const std::string& _dataIn, std::string& _dataOut);
    void startServer(sGSocket& _socket);
    void startServer(void* _onStart);
};
//==============================================
#endif
//==============================================
