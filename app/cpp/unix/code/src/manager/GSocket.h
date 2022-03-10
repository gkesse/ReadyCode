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
    //
    void createDoms();
    std::string getSocketItem(const std::string& _data) const;
    //
    int loadDomain() const;
    int loadType() const;
    int loadProtocol() const;
    int loadFamily() const;
    //
    void createSocket(int _domain, int _type, int _protocol);
    void createAddress(int _family, std::string _ip, int _port);
    void listenSocket(int _backlog);
    void bindSocket();
    void connectSocket();
    void startMessage();
    void acceptSocket(GSocket& _socket);
    int recvData(std::string& _data);
    int recvData(GSocket& _socket, std::string& _data);
    int readData(std::string& _data);
    int sendData(const std::string& _data);
    int sendData(GSocket& _socket, const std::string& _data);
    int writeData(const std::string& _data);
    std::string readAddressIp() const;
    void closeSocket();
    void startServerTcp();
    static void* onServerTcp(GSocket* _client);
    std::string callServerTcp(const std::string& _dataIn);

protected:
    static const int BUFFER_DATA_SIZE = 1024;
    static const int BUFFER_IP_SIZE = 32;
    //
    int m_socket;
    struct sockaddr_in m_address;
};
//==============================================
#endif
//==============================================
