//===============================================
#include "GAsio.h"
//===============================================
GAsio::GAsio() {
	m_port = 8585;
	m_backlog = 30;
	m_ip = "0.0.0.0";
	m_endpoint = 0;
	m_acceptor = 0;
	m_socket = 0;
}
//===============================================
GAsio::~GAsio() {
	if(m_endpoint) {delete m_endpoint; m_endpoint = 0;}
	if(m_acceptor) {delete m_acceptor; m_acceptor = 0;}
}
//===============================================
void GAsio::port(int _port) {
	m_port = _port;
}
//===============================================
void GAsio::backlog(int _backlog) {
	m_backlog = _backlog;
}
//===============================================
void GAsio::ip(const std::string& _ip) {
	m_ip = _ip;
}
//===============================================
void GAsio::endpoint() {
	m_endpoint = new boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::from_string(m_ip), m_port);
}
//===============================================
void GAsio::acceptor() {
	m_acceptor = new boost::asio::ip::tcp::acceptor(m_ios, m_endpoint->protocol());
}
//===============================================
void GAsio::bind() {
	m_acceptor->bind(*m_endpoint, m_errorcode);
}
//===============================================
void GAsio::listen() {
	m_acceptor->listen(m_backlog);
}
//===============================================
void GAsio::socket() {
	m_socket = new boost::asio::ip::tcp::socket(m_ios);
}
//===============================================
void GAsio::accept() {
	m_acceptor->accept(*m_socket);
}
//===============================================
void GAsio::start() {
	printf("demarrage du serveur...\n");
}
//===============================================
