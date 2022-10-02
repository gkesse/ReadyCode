//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
class GSocket : public GObject {
public:
    GSocket();
    virtual ~GSocket();
    void setMajor(int _major);
    void setMinor(int _minor);
    void setDomain(int _domain);
    void setType(int _type);
    void setProtocol(int _protocol);
    void setFamily(int _family);
    void setPort(int _port);
    void setHostname(const GString& _hostname);

    bool callServer();

    virtual bool createData();
    virtual bool onCallServer();

    bool sendData();

    int readData(char* _data, int _size);
    bool readData(int _diffSize);
    bool readMethod();

protected:
    static const int BUFFER_SIZE = 1024;
    static const int METHOD_SIZE = 1024;

    int m_major;
    int m_minor;
    int m_domain;
    int m_type;
    int m_protocol;
    int m_family;
    int m_port;
    GString m_hostname;

    GString m_dataIn;
    GString m_dataOut;
    SOCKET m_socket;
};
//==============================================
#endif
//==============================================
