//===============================================
#include "GXmlRpc.h"
//===============================================
GXmlRpc::GXmlRpc() {

}
//===============================================
GXmlRpc::~GXmlRpc() {

}
//===============================================
void GXmlRpc::method(xmlrpc_c::method* _method) {
	m_method.reset(_method);
}
//===============================================
