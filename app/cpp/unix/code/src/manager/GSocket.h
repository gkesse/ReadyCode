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
    void createAddress(int _family, GString _ip, int _port);
    void listenSocket(int _backlog);
    void bindSocket();
    void connectSocket();
    void startMessage();
    void acceptSocket(GSocket& _socket);
    void acceptSocket(GSocket* _socket);
    int recvData(GString& _data);
    int recvData(GString& _data, int _size);
    int recvData(GSocket& _socket, GString& _data);
    int readData(GString& _data);
    int sendData(const GString& _data);
    int sendData(GSocket& _socket, const GString& _data);
    int writeData(const GString& _data);
    void closeSocket();
    void startServer(void* _onServerTcp);
    static void* onServerThread(GSocket* _client);
    GString callServer(const GString& _dataIn);
    //
    void setReq(const GString& _req);
    GString toReq() const;
    std::queue<GSocket*>& getClientIns();
    void addResponse(const GString& _data, bool _isRoot = true);
    bool clearErrors();
    bool clearLogs();
    bool addErrors();
    void sendResponse();
    //
    GString readAddressIp() const;

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
    GString m_req;
};
//==============================================
#endif
//==============================================
