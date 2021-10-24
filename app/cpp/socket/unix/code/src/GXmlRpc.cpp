//===============================================
#include "GXmlRpc.h"
//===============================================
GXmlRpc::GXmlRpc() {
	m_port = 8585;
	m_method = 0;
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
}
//===============================================
void GXmlRpc::name(const std::string& _name) {
	m_name = _name;
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
void GXmlRpc::method(xmlrpc_c::method* _method) {
	m_method = _method;
}
//===============================================
void GXmlRpc::registry() {
	m_registry.addMethod(m_name, m_method);
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
void GXmlRpc::call() {
    m_client.call(m_url, m_name, "ii", &m_result, 5, 7);
}
//===============================================
void GXmlRpc::start() {
	printf("Demarrage du serveur...\n");
}
//===============================================
