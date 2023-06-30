//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
class GSocket : public GObject {
public:
    GSocket();
    ~GSocket();
    GLog& getSrvLogs();
    GString toHostname(const GString& _facade) const;
    int toPort(const GString& _facade) const;
    void checkErrors(GString& _data);
    void runServer();
    static DWORD WINAPI onThread(LPVOID _params);
    GString callSocket(const GString& _data, const GString& _facade = "facade");
    GString callServer(const GString& _data, const GString& _facade = "facade");
    GString callFacade(const GString& _module, const GString& _method, const GString& _data = "");
    void sendData(const GString& _data);
    GString readData();

private:
    static const int BUFFER_SIZE = 1024;        // 1 Ko
    static const int BUFFER_MAX = 1*1024*1024;  // 1 Mo

private:
    SOCKET m_socket;
    GLog m_srvLogs;
};
//===============================================
#endif
//===============================================
