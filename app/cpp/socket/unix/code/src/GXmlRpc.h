//===============================================
#ifndef _GXmlRpc_
#define _GXmlRpc_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GXmlRpc {
public:
    GXmlRpc();
    ~GXmlRpc();
    void port(int _port);
    void name(const std::string& _name);
    void method(xmlrpc_c::method* _method);
    void registry();
    void server();
    void run();
    
protected:
    xmlrpc_c::method* m_method;
    xmlrpc_c::registry m_registry;
    xmlrpc_c::serverAbyss m_server;
    std::string m_name;
    int m_port;
};
//==============================================
#endif
//==============================================
