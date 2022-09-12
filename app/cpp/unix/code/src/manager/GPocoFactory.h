//===============================================
#ifndef _GPocoFactory_
#define _GPocoFactory_
//===============================================
#include "GInclude.h"
//===============================================
class GPocoFactory : public Poco::Net::TCPServerConnectionFactory {
public:
    GPocoFactory();
    ~GPocoFactory();
    void setModule(const std::string& _module);
    void setFormat(const std::string& _format);
    Poco::Net::TCPServerConnection* onCreateConnectionTcp(const Poco::Net::StreamSocket& _socket);
    Poco::Net::TCPServerConnection* onCreateConnectionTime(const Poco::Net::StreamSocket& _socket);

protected:
    Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& _socket);

private:
    std::string m_module;
    std::string m_format;
};
//==============================================
#endif
//==============================================
