//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
class GCode;
//===============================================
class GSocket : public GObject {
public:
    GSocket();
    ~GSocket();
    //
    void createDoms();
    //
    int loadDomain() const;
    int loadType() const;
    int loadProtocol() const;
    int loadFamily() const;
    int loadPort() const;
    int loadPort(int _isTestEnv) const;
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
    int recvData(std::string& _data, int _size);
    int recvData(GSocket& _socket, std::string& _data);
    int readData(std::string& _data);
    int sendData(const std::string& _data);
    int sendData(GSocket& _socket, const std::string& _data);
    int writeData(const std::string& _data);
    void closeSocket();
    void startServer(void* _onServerTcp);
    static void* onServerThread(GSocket* _client);
    std::string callServer(const std::string& _dataIn);
    //
    void setReq(const std::string& _req);
    std::string toReq() const;
    std::queue<GSocket*>& getClientIns();
    void addResponse(const std::string& _data, bool _isRoot = true);
    bool addErrors();
    void sendResponse();
    //
    std::string readAddressIp() const;

private:
    static const int BUFFER_DATA_SIZE = 1024;
    static const int BUFFER_NDATA_SIZE = 256;
    static const int BUFFER_HOSTNAME_SIZE = 256;
    //
    int m_socket;
    struct sockaddr_in m_address;
    //
    GSocket* m_server;
    std::queue<GSocket*> m_clientIns;
    std::shared_ptr<GCode> m_res;
    std::string m_req;
};
//==============================================
#endif
//==============================================
