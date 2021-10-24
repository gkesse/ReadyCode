//===============================================
#include "GXmlRpc.h"
//===============================================
GXmlRpc::GXmlRpc() {
	m_port = 8585;
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
void GXmlRpc::method(xmlrpc_c::methodPtr _method) {
	m_method = _method;
}
//===============================================
void GXmlRpc::server() {
	xmlrpc_c::registry lRegistry;
	lRegistry.addMethod(m_name, m_method);
	xmlrpc_c::serverAbyss lServer(
			xmlrpc_c::serverAbyss::constrOpt()
			.registryP(&lRegistry)
			.portNumber(m_port)
	);
	lServer.run();
}
//===============================================
