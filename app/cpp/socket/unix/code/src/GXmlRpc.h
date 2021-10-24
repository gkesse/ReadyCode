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
    void server();
    
protected:
    xmlrpc_c::method* m_method;
    xmlrpc_c::registry m_registry;
    std::string m_name;
    int m_port;
};
//==============================================
#endif
//==============================================
