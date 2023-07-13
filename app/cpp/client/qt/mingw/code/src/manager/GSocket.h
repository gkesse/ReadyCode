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
    int toPort() const;
    void checkErrors(GString& _data);
    GString callServer(const GString& _data);
    GString callSocket(const GString& _data);
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
