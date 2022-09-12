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
    void setModule(const std::string& _key);
    void setFormat(const std::string& _format);
    void onRunTcp();
    void onRunTime();

protected:
    void run();

private:
    static const int BUFFER_SIZE = 10;
    std::string m_module;
    std::string m_hostname;
    std::string m_format;
};
//==============================================
#endif
//==============================================
