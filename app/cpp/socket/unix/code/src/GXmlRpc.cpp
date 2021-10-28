//===============================================
#include "GXmlRpc.h"
//===============================================
GXmlRpc::GXmlRpc() {
    m_port = 8585;
    m_scheme = "http";
    m_host = "localhost";
    url();
}
//===============================================
GXmlRpc::~GXmlRpc() {

}
//===============================================
void GXmlRpc::port(int _port) {
    m_port = _port;
    url();
}
//===============================================
void GXmlRpc::host(const std::string& _host) {
    m_host = _host;
    url();
}
//===============================================
void GXmlRpc::scheme(const std::string& _scheme) {
    m_scheme = _scheme;
    url();
}
//===============================================
void GXmlRpc::url() {
    m_url = "";
    m_url += m_scheme;
    m_url += "://";
    m_url += m_host;
    m_url += ":";
    m_url += std::to_string(m_port);
    m_url += "/";
    m_url += "RPC2";
}
//===============================================
void GXmlRpc::url(const std::string& _url) {
    m_url = _url;
}
//===============================================
void GXmlRpc::addMethod(const std::string& _name, pMethod* _method) {
    m_registry.addMethod(_name, _method);
}
//===============================================
void GXmlRpc::server() {
    m_server.reset(
            new xmlrpc_c::serverAbyss(
                    xmlrpc_c::serverAbyss::constrOpt()
                    .registryP(&m_registry)
                    .portNumber(m_port)
            )
    );
}
//===============================================
void GXmlRpc::run() {
    m_server->run();
}
//===============================================
void GXmlRpc::start() {
    printf("Demarrage du serveur...\n");
}
//===============================================
void GXmlRpc::print() const {
    std::cout << m_data << "\n";
}
//===============================================
void GXmlRpc::onAdd(GXmlRpcM::pList _params, GXmlRpcM::pValue _value) {
    int lA(_params.getInt(0));
    int lB(_params.getInt(1));
    _params.verifyEnd(2);
    int lC = lA + lB;
    *_value = xmlrpc_c::value_int(lC);
}
//===============================================
void GXmlRpc::call(const std::string& _name, const std::string& _format, int _A, int _B) {
    m_client.call(m_url, _name, _format, &m_result, _A, _B);
    m_data = std::to_string(xmlrpc_c::value_int(m_result));
}
//===============================================
