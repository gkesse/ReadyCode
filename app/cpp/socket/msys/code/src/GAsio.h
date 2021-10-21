//===============================================
#ifndef _GAsio_
#define _GAsio_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GAsio {
public:
    GAsio();
    ~GAsio();
    void port(int _port);
    void backlog(int _backlog);
    void ip(const std::string& _ip);
    void endpoint();
    void acceptor();
    void bind();
    void listen();
    void socket();
    void accept();
    void start();
    
protected:
    int m_port;
    int m_backlog;
    std::string m_ip;
    boost::asio::ip::tcp::endpoint* m_endpoint;
    boost::asio::io_service m_ios;
    boost::asio::ip::tcp::acceptor* m_acceptor;
    boost::asio::ip::tcp::socket* m_socket;
    boost::system::error_code m_errorcode;
};
//==============================================
#endif
//==============================================
