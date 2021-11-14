//===============================================
#include "GAsio.h"
//===============================================
GAsio::GAsio() {
    m_port = 8585;
    m_backlog = 30;
    m_ip = "0.0.0.0";
    m_bytes = -1;
}
//===============================================
GAsio::~GAsio() {

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
void GAsio::address() {
    m_address = boost::asio::ip::address::from_string(m_ip);
}
//===============================================
void GAsio::endpoint() {
    m_endpoint = boost::make_shared<boost::asio::ip::tcp::endpoint>(m_address, m_port);
}
//===============================================
void GAsio::acceptor() {
    m_acceptor = boost::make_shared<boost::asio::ip::tcp::acceptor>(m_ios, *m_endpoint);
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
    m_socket = boost::make_shared<boost::asio::ip::tcp::socket>(m_ios);
}
//===============================================
void GAsio::socket(socket_ptr _socket) {
    m_socket = _socket;
}
//===============================================
GAsio::socket_ptr GAsio::socket2() {
    return m_socket;
}
//===============================================
void GAsio::accept() {
    m_acceptor->accept(*m_socket);
}
//===============================================
void GAsio::connect() {
    m_socket->connect(*m_endpoint);
}
//===============================================
void GAsio::onAsync(onAsyncCB _func) {
    m_socket->async_connect(*m_endpoint, _func);
}
//===============================================
void GAsio::error(const error_ptr& _errorcode) {
    m_errorcode = _errorcode;
}
//===============================================
void GAsio::run() {
    m_ios.run();
}
//===============================================
void GAsio::send(const std::string& _data) {
    m_socket->send(boost::asio::buffer(_data));
}
//===============================================
void GAsio::recv() {
    m_bytes = m_socket->read_some(boost::asio::buffer(m_buffer), m_errorcode);
    m_buffer[m_bytes] = 0;
}
//===============================================
void GAsio::thread(onThreadCB _func, GAsio::socket_ptr _socket) {
    boost::thread(boost::bind(_func, _socket));
}
//===============================================
void GAsio::start() const {
    printf("demarrage du serveur...\n");
}
//===============================================
void GAsio::print() const {
    printf("%s\n", m_buffer.data());
}
//===============================================
void GAsio::print2() const {
    if(m_errorcode) {
        printf("L'operation a echoue...\n");
    }
    else {
        printf("L'operation a reussi...\n");
    }
}
//===============================================
