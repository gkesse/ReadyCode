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
    void init();
    void sockets();
    void address();
    void listens();
    void binds();
    void connects();
    void accepts(GSocket& _socket);
    void recvs();
    void sends(const char* _data);
    void print() const;
    void close();
    void clean();
    
protected:
    const int BUFFER_SIZE = 1024;
    char m_buffer[BUFFER_SIZE + 1];
    GString m_data;
    SOCKET m_socket;
    SOCKADDR_IN m_address;
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
