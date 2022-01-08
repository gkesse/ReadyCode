//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
#define GSOCKET GSocket::Instance()
//===============================================
class GSocket : public GObject {
public:
    GSocket(bool _init = false);
    ~GSocket();
    static GSocket* Instance();
    //
    void createDoms();
    int getMajor() const;
    int getMinor() const;
    bool getVersionShow() const;
    bool getHostnameShow() const;
    bool getAddressIpShow() const;
    bool getWelcomShow() const;
    bool getDebugShow() const;
    std::string getAddressClient() const;
    std::string getAddressServer() const;
    int getPort() const;
    int getBacklog() const;
    //
    void initSocket(int _major, int _minor);
    bool createSocketTcp();
    bool cretaeSocketUdp();
    void createAddress(const std::string& _ip, int _port);
    bool listenSocket(int _backlog);
    bool bindSocket();
    bool connectToServer();
    bool acceptConnection(GSocket& _socket);
    int recvData(std::string& _data);
    int readData(std::string& _data);
    int recvData(GSocket& _socket, std::string& _data);
    void sendData(const std::string& _data);
    void writeData(const std::string& _data);
    void sendData(GSocket& _socket, const std::string& _data);
    std::string getAddressIp() const;
    std::string getHostname() const;
    void shutdownWR();
    void shutdownRD();
    void closeSocket();
    void cleanSocket();
    //
    void startServerTcp();
    void callServerTcp(const std::string& _dataIn, std::string& _dataOut);
    //
    static DWORD WINAPI onServerTcp(LPVOID _params);
    std::queue<std::string>& getDataIn() const;
    std::queue<GSocket*>& getClientIn() const;
    int& getMessageId() const;
    void showMessage(const std::string& _dataIn) const;
    void addDataOut(const std::string& _dataOut);
    std::string getDataOut() const;
    void resultOk();

private:
    static const int BUFFER_SIZE = 1024;
    static const int HOSTNAME_SIZE = 256;

private:
    static GSocket* m_instance;
    SOCKET m_socket;
    SOCKADDR_IN m_address;
    //
    static std::queue<std::string> m_dataIn;
    static std::queue<GSocket*> m_clientIn;
    std::vector<std::string> m_dataOut;
    //
    static int m_messageId;
};
//==============================================
#endif
//==============================================
