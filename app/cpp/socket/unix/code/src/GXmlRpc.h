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
    void method(xmlrpc_c::methodPtr _method);
    void server();
    
protected:
    xmlrpc_c::methodPtr m_method;
    std::string m_name;
    int m_port;
};
//==============================================
#endif
//==============================================
