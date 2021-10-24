//===============================================
#ifndef _GXmlRpc_
#define _GXmlRpc_
//===============================================
#include "GInclude.h"
#include "GXmlRpcM.h"
//===============================================
class GXmlRpc {
public:
    GXmlRpc();
    ~GXmlRpc();
    void port(int _port);
    void name(const std::string& _name);
    void url();
    void url(const std::string& _url);
    void method(xmlrpc_c::method* _method);
    void registry();
    void server();
    void run();
    void call();
    void start();
    void toInt();
    void print() const;
    void onAdd(GXmlRpcM::pList _params, GXmlRpcM::pValue _value);

protected:
    xmlrpc_c::method* m_method;
    xmlrpc_c::registry m_registry;
    std::shared_ptr<xmlrpc_c::serverAbyss> m_server;
    xmlrpc_c::clientSimple m_client;
    xmlrpc_c::value m_result;
    std::string m_name;
    std::string m_url;
    std::string m_scheme;
    std::string m_host;
    std::string m_data;
    int m_port;
};
//==============================================
#endif
//==============================================
