//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GInclude.h"
//===============================================
class GCode;
//===============================================
class GSocket {
public:
    GSocket();
    ~GSocket();
    static GSocket* Instance();
    //
    void createDoms();
    QString getItem(const QString& _key, const QString& _data) const;
    QString getErrorMsg(const QString& _code, const QString& _lang) const;
    //
    int loadDomain() const;
    int loadType() const;
    int loadProtocol() const;
    int loadFamily() const;
    int loadPort() const;
    int loadPort(int _isTestEnv) const;
    QString loadErrorMsg() const;
    //
    bool initSocket(int _major, int _minor);
    bool createSocket(int _domain, int _type, int _protocol);
    bool createAddress(int _family, const QString& _addressIp, int _port);
    bool listenSocket(int _backlog);
    bool bindSocket();
    bool connectSocket();
    bool startMessage();
    bool acceptSocket(GSocket& _socket);
    bool acceptSocket(GSocket* _socket);
    int recvData(QString& _data);
    int recvData(QString& _data, int _size);
    int recvData(GSocket& _socket, QString& _data);
    int readData(QString& _data);
    int readPack(QString& _data);
    int sendData(const QString& _data);
    int sendData(GSocket& _socket, const QString& _data);
    int writeData(const QString& _data);
    int writePack(const QString& _data);
    QString loadAddressIp() const;
    QString getHostname() const;
    bool closeSocket();
    bool cleanSocket();
    void startServer(void* _onServerThread);
    static DWORD WINAPI onServerThread(LPVOID _params);
    QString callServer(const QString& _dataIn);
    QString callServer(const QString& _module, const QString& _method, const QString& _data = "");
    //
    void setReq(const QString& _req);
    QString toReq() const;
    QStack<GSocket*>& getClientIns();
    //
    bool addErrors();
    bool sendResponse();

private:
    QSharedPointer<GCode> m_dom;
    QSharedPointer<GCode> m_domWsaError;
    QSharedPointer<GCode> m_res;
    QString m_req;
    //
    static const int BUFFER_DATA_SIZE = 1024;
    static const int BUFFER_NDATA_SIZE = 256;
    static const int BUFFER_HOSTNAME_SIZE = 256;
    //
    SOCKET m_socket;
    SOCKADDR_IN m_address;
    //
    GSocket* m_server;
    QStack<GSocket*> m_clientIns;
};
//==============================================
#endif
//==============================================
