//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
#include "GThread.h"
#include "GTimer.h"
//===============================================
#define GSOCKET GSocket::Instance()
//===============================================
class GSocket : public GObject {
public:
    GSocket();
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
    void stopServer();
    bool isServerOn() const;
    //
    void startServerTcp();
    void callServerTcp(const std::string& _dataIn, std::string& _dataOut);
    void callServerTcp(const GObject& _request, std::string& _dataOut);
    void setOnServerTcp(GThread::onThreadCB _onServerTcp);
    static DWORD WINAPI onServerTcp(LPVOID _params);
    //
    void startClientTcp();
    void setOnClientTcp(GTimer::onTimerCB _onClientTcp);
    static void CALLBACK onClientTcp(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    //
    std::queue<GSocket*>& getClientIn();
    //
    GSocket* getServer() const;
    //
    std::string getRequest() const;
    void setRequest(const std::string& _request);
    //
    void showMessage(const std::string& _data) const;
    //
    void addDataIn(const std::string& _data);
    void addDataIn(const GObject& _data);
    std::queue<std::string>& getDataIn();
    //
    void addDataAns(const std::string& _data);
    std::queue<std::string>& getDataAns();
    //
    void addDataOut(const std::string& _data);
    void addDataOut(const GObject& _data);
    std::string getDataOut() const;
    //
    void addResultOk(const std::string& _data);
    void addResultOk(const GObject& _data);
    //
    void addErrors(const std::string& _data);
    void addErrors(const GObject& _data);
    //
    void sendResponse();
    //
    bool setOption();
    void clearDescriptor();
    void setDescriptor();
    bool selectDescriptor();
    bool issetDescriptor();
    //
    void addClient(const std::string& _id, GSocket* _socket);

private:
    static const int BUFFER_SIZE = 1024;
    static const int HOSTNAME_SIZE = 256;
    //
    static GSocket* m_instance;
    static GSocket* m_socketObj;
    static int m_messageId;
    //
    SOCKET m_socket;
    SOCKADDR_IN m_address;
    //
    std::queue<GSocket*> m_clientIn;
    std::queue<std::string> m_dataIn;
    std::queue<std::string> m_dataAns;
    //
    std::vector<std::string> m_dataOut;
    std::vector<std::string> m_resultOk;
    std::vector<std::string> m_errors;
    //
    bool m_serverOn;
    //
    GThread::onThreadCB m_onServerTcp;
    GTimer::onTimerCB m_onClientTcp;
    //
    fd_set m_descriptor;
    int m_option;
    //
    std::map<std::string, GSocket*> m_clientMap;
    //
    std::string m_request;
    GSocket* m_server;
};
//==============================================
#endif
//==============================================
