//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GManager.h"
#include "GHttp.h"
//===============================================
class GSocket;
class GOpenSSL;
//===============================================
class GServer : public GManager {
public:
    GServer();
    ~GServer();
    bool isValid(GString& _data);
    bool isHttp(GString& _data);
    GString toHttp(const GString& _data, const GHttp::eGStatus& _status);
    void sendResponse(GSocket* _socket);
    void sendResponse(GOpenSSL* _socket);
    void run(GString& _data);
    void runFacade(const GString& _data);
    void runMaster(const GString& _data);
    void runCalculator(const GString& _data);
    void runUser(const GString& _data);
    void runFile(const GString& _data);

private:
    bool m_isHttp;
};
//===============================================
#endif
//===============================================
