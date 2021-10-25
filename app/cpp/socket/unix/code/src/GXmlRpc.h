//===============================================
#ifndef _GXmlRpc_
#define _GXmlRpc_
//===============================================
#include "GInclude.h"
#include "GXmlRpcM.h"
//===============================================
class GXmlRpc {
public:
	typedef xmlrpc_c::method pMethod;

public:
    GXmlRpc();
    ~GXmlRpc();
    void port(int _port);
    void host(const std::string& _host);
    void scheme(const std::string& _scheme);
    void url();
    void url(const std::string& _url);
    void addMethod(const std::string& _name, pMethod* _method);
    void server();
    void run();
    void start();
    void print() const;
    void onAdd(GXmlRpcM::pList _params, GXmlRpcM::pValue _value);
    void call(const std::string& _name, const std::string& _fromat, int _A, int _B);

protected:
    xmlrpc_c::registry m_registry;
    std::shared_ptr<xmlrpc_c::serverAbyss> m_server;
    xmlrpc_c::clientSimple m_client;
    xmlrpc_c::value m_result;
    std::string m_url;
    std::string m_scheme;
    std::string m_host;
    std::string m_data;
    int m_port;
};
//==============================================
#endif
//==============================================
