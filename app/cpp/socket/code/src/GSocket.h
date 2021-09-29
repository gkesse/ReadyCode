//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GSocket {
public:
    GSocket();
    virtual ~GSocket();
    void setAddress(const std::string& data);
    void setPort(int data);
    void setListen(int listen);
    virtual void startTCP();
    virtual void callTCP(const char* dataIn, GString& dataOut);
    
protected:
    const int BUFFER_SIZE = 8;
    std::string m_address;
    int m_port;
    int m_listen;
};
//==============================================
#endif
//==============================================
