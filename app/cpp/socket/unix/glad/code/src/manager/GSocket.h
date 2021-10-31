//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GSocket {
public:
    GSocket();
    ~GSocket();
    void ip(const std::string& _ip);
    void port(int _port);
    void backlog(int _backlog);
    void sockets();
    void sockets2();
    void address();
    void listens();
    void binds();
    void connects();
    void start();
    void accepts(GSocket& _socket);
    void recvs();
    void recvs(GSocket& _socket);
    void recvs(GString& _data);
    void sends(const char* _data);
    void sends(GSocket& _socket, const char* _data);
    void sends(const GString& _data);
    void ip();
    void print() const;
    void print2() const;
    void closes();
    
protected:
    static const int BUFFER_DATA_SIZE = 1024;
    static const int BUFFER_IP_SIZE = 32;
    char m_buffer[BUFFER_DATA_SIZE + 1];
    char m_ip2[BUFFER_IP_SIZE + 1];
    int m_socket;
    struct sockaddr_in m_address;
    int m_size;
    int m_bytes;
    std::string m_ip;
    int m_port;
    int m_backlog;
    int m_major;
    int m_minor;
};
//==============================================
#endif
//==============================================
