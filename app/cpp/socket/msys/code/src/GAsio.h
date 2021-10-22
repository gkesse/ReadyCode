//===============================================
#ifndef _GAsio_
#define _GAsio_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GAsio {
public:
	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
	typedef void (*onThreadCB)(socket_ptr _socket);

public:
    GAsio();
    ~GAsio();
    void port(int _port);
    void backlog(int _backlog);
    void ip(const std::string& _ip);
    void address();
    void endpoint();
    void acceptor();
    void bind();
    void listen();
    void socket();
    void socket(GAsio::socket_ptr _socket);
    GAsio::socket_ptr socket2();
    void accept();
    void connect();
    void send(const std::string& _data);
    void recv();
    void thread(GAsio::onThreadCB _func, GAsio::socket_ptr _socket);
    void start() const;
    void print() const;
    
protected:
    static const int BUFFER_DATA_SIZE = 1024;
    int m_port;
    int m_backlog;
    int m_bytes;
    std::string m_ip;
    boost::array<char, BUFFER_DATA_SIZE + 1> m_buffer;
    boost::asio::ip::address m_address;
    boost::asio::io_service m_ios;
    boost::system::error_code m_errorcode;
    boost::shared_ptr<boost::asio::ip::tcp::endpoint> m_endpoint;
    boost::shared_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;
    boost::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
};
//==============================================
#endif
//==============================================
