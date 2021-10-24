//===============================================
#include "GXmlRpc.h"
//===============================================
GXmlRpc::GXmlRpc() {
	m_port = 8585;
	m_method = 0;
}
//===============================================
GXmlRpc::~GXmlRpc() {

}
//===============================================
void GXmlRpc::port(int _port) {
	m_name = _port;
}
//===============================================
void GXmlRpc::name(const std::string& _name) {
	m_name = _name;
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
	m_server = xmlrpc_c::serverAbyss(
			xmlrpc_c::serverAbyss::constrOpt()
			.registryP(&m_registry)
			.portNumber(m_port)
	);
}
//===============================================
void GXmlRpc::run() {
	m_server.run();
}
//===============================================
