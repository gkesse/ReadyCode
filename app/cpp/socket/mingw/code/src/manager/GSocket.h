//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GInclude.h"
//===============================================
class GSocket {
public:
    GSocket();
    ~GSocket();
    void init(int _major, int _minor);
    void sockets();
    void sockets2();
    void address(const std::string& _ip, int _port);
    void listens(int _backlog);
    void binds();
    void connects();
    void accepts(GSocket& _socket);
    int recvs(std::string& _data);
    int reads(std::string& _data);
    int recvs(GSocket& _socket, std::string& _data);
    void sends(const std::string& _data);
    void writes(const std::string& _data);
    void sends(GSocket& _socket, const std::string& _data);
    void ip(std::string& _ip);
    void hostname(std::string& _hostname);
    void shutdownWR();
    void shutdownRD();
    void close();
    void clean();
    void start(sGSocket& _socket);
    void call(sGSocket& _socket, const std::string& _write, std::string& _read);
    
protected:
    static const int BUFFER_SIZE = 1024;
    static const int IP_SIZE = 256;
    static const int HOSTNAME_SIZE = 256;
    SOCKET m_socket;
    SOCKADDR_IN m_address;
};
//==============================================
#endif
//==============================================
