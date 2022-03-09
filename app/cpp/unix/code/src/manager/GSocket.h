//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
class GSocket : public GObject {
public:
    GSocket();
    ~GSocket();
    void setAddressIp(const std::string& _ip);
    void setPort(int _port);
    void setBacklog(int _backlog);
    void createSocket();
    void createAddress();
    void listenSocket();
    void bindSocket();
    void connectSocket();
    void start();
    void acceptSocket(GSocket& _socket);
    int recvData(std::string& _data);
    int recvData(GSocket& _socket, std::string& _data);
    int recvData(std::string& _data);
    int sendData(const std::string& _data);
    int sendData(GSocket& _socket, const std::string& _data);
    int sendData(const std::string& _data);
    std::string readAddressIp() const;
    void closeSocket();
    
protected:
    static const int BUFFER_DATA_SIZE = 1024;
    static const int BUFFER_IP_SIZE = 32;
    //
    int m_socket;
    struct sockaddr_in m_address;
    //
    std::string m_ip;
    int m_port;
    int m_backlog;
    int m_domain;
    int m_type;
    int m_protocol;
    sa_family_t m_family;
    int m_familyIp;
};
//==============================================
#endif
//==============================================
