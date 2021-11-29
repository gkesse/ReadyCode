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
    void createPoint(std::string& _data, const std::string& _x, const std::string& _y, const std::string& _z);
    void callServer(const std::string& _dataIn, std::string& _dataOut);
    void startServer(sGSocket& _socket);
    void startServer(void* _onStart);
};
//==============================================
#endif
//==============================================
