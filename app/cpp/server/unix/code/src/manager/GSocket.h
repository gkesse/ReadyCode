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
    GString toHostname(const GString& _facade) const;
    int toPort(const GString& _facade) const;
    int toPortCpp() const;
    void checkErrors(GString& _data);
    void runServer();
    static void* onThreadCB(void* _params);
    GString callSocket(const GString& _data, const GString& _facade = "facade");
    GString callServer(const GString& _data, const GString& _facade = "facade");
    GString callFacade(const GString& _module, const GString& _method, const GString& _data = "");
    void sendData(const GString& _data);
    GString readData();
    int getTotal(const GString& _data) const;

private:
    static const int BUFFER_SIZE = 1024;        // 1 Ko
    static const int BUFFER_MAX = 1*1024*1024;  // 1 Mo

private:
    int m_socket;
};
//===============================================
#endif
//===============================================
