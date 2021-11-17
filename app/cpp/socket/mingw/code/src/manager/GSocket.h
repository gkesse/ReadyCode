//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
class GSocket {
public:
    GSocket();
    ~GSocket();
    void initSocket(int _major, int _minor);
    void createSocketTcp();
    void cretaeSocketUdp();
    void createAddress(const std::string& _ip, int _port);
    void listenSocket(int _backlog);
    void bindSocket();
    void connectToServer();
    void acceptConnection(GSocket& _socket);
    int recvData(std::string& _data);
    int readData(std::string& _data);
    int recvData(GSocket& _socket, std::string& _data);
    void sendData(const std::string& _data);
    void writeData(const std::string& _data);
    void sendData(GSocket& _socket, const std::string& _data);
    void getAddressIp(std::string& _ip);
    void getHostname(std::string& _hostname);
    void shutdownWR();
    void shutdownRD();
    void closeSocket();
    void cleanSocket();
    
protected:
    static const int BUFFER_SIZE = 1024;
    static const int HOSTNAME_SIZE = 256;
    SOCKET m_socket;
    SOCKADDR_IN m_address;
};
//==============================================
#endif
//==============================================
