//===============================================
#ifndef _GSocket2_
#define _GSocket2_
//===============================================
#include "GObject.h"
//===============================================
class GSocket2 {
public:
    GSocket2();
    ~GSocket2();
    void setMajor(int _major);
    void setMinor(int _minor);
    void setDomain(int _domain);
    void setType(int _type);
    void setProtocol(int _protocol);
    void setFamily(int _family);
    void setPort(int _port);
    void setHostname(const QString& _hostname);
    bool callServer(const QString& _dataIn, QString& _dataOut);

private:
    int m_major;
    int m_minor;
    int m_domain;
    int m_type;
    int m_protocol;
    int m_family;
    int m_port;
    QString m_hostname;
};
//==============================================
#endif
//==============================================
