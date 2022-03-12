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
    void acceptSocket(GSocket* _socket);
    int recvData(std::string& _data);
    int recvData(GSocket& _socket, std::string& _data);
    int readData(std::string& _data);
    int sendData(const std::string& _data);
    int sendData(GSocket& _socket, const std::string& _data);
    int writeData(const std::string& _data);
    void closeSocket();
    void startServerTcp(void* _onServerTcp);
    static void* onServerTcp(GSocket* _client);
    std::string callServerTcp(const std::string& _dataIn);
    //
    std::queue<std::string>& getDataIns();
    std::queue<GSocket*>& getClientIns();

private:
    static const int BUFFER_DATA_SIZE = 1024;
    static const int BUFFER_HOSTNAME_SIZE = 256;
    //
    int m_socket;
    struct sockaddr_in m_address;
    //
    GSocket* m_server;
    std::queue<std::string> m_dataIns;
    std::queue<GSocket*> m_clientIns;

public:
    pthread_mutex_t m_mutex;
};
//==============================================
#endif
//==============================================
