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
    void runServer();
    static DWORD WINAPI onThread(LPVOID _params);
    GString toHostname(const GString& _facade) const;
    int toPort(const GString& _facade) const;
    GString callServer(const GString& _data, const GString& _facade = "facade");
    GString callFacade(const GString& _module, const GString& _method, const GString& _data = "");
    void sendData(const GString& _data);
    GString readData();

private:
    static const int BUFFER_SIZE = 1024;

private:
    SOCKET m_socket;
};
//===============================================
#endif
//===============================================
