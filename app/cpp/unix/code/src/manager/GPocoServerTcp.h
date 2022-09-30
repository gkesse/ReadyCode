//===============================================
#ifndef _GPocoServerTcp_
#define _GPocoServerTcp_
//===============================================
#include "GInclude.h"
//===============================================
class GPocoServerTcp : public Poco::Net::TCPServerConnection {
public:
    typedef Poco::Net::TCPServerConnectionFactoryImpl<GPocoServerTcp> GFactory;

public:
    GPocoServerTcp(const Poco::Net::StreamSocket& _socket);
    ~GPocoServerTcp();
    void setModule(const GString& _key);
    void setFormat(const GString& _format);
    void onRunTcp();
    void onRunTime();

protected:
    void run();

private:
    static const int BUFFER_SIZE = 10;
    GString m_module;
    GString m_hostname;
    GString m_format;
};
//==============================================
#endif
//==============================================
