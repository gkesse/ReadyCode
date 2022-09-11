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

protected:
    void run();
};
//==============================================
#endif
//==============================================
