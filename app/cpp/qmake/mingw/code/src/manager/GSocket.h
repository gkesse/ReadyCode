//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
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
    GSocket& initSocket(int _major, int _minor);
    GSocket& createSocket(int _domain, int _type, int _protocol);
    GSocket& createAddress(int _family, const QString& _addressIp, int _port);
    GSocket& listenSocket(int _backlog);
    GSocket& bindSocket();
    GSocket& connectSocket();
    void startMessage();
    GSocket& acceptSocket(GSocket& _socket);
    GSocket& acceptSocket(GSocket* _socket);
    int recvData(QString& _data);
    int recvData(GSocket& _socket, QString& _data);
    int readData(QString& _data);
    int sendData(const QString& _data);
    int sendData(GSocket& _socket, const QString& _data);
    int writeData(const QString& _data);
    QString loadAddressIp() const;
    QString getHostname() const;
    void closeSocket();
    void cleanSocket();
    void startServer(void* _onServerThread);
    static DWORD WINAPI onServerThread(LPVOID _params);
    QString callServer(const QString& _dataIn);
    //
    void setRequest(const QString& _req);
    QString getRequest() const;
    QStack<GSocket*>& getClientIns();
    QSharedPointer<GCode>& getResponse();

private:
    QSharedPointer<GXml> m_dom;
    QSharedPointer<GXml> m_domWsaError;
    QSharedPointer<GCode> m_res;
    //
    static const int BUFFER_DATA_SIZE = 1024;
    static const int BUFFER_NDATA_SIZE = 1024;
    static const int BUFFER_HOSTNAME_SIZE = 256;
    //
    SOCKET m_socket;
    SOCKADDR_IN m_address;
    //
    GSocket* m_server;
    QStack<GSocket*> m_clientIns;
    QString m_request;
};
//==============================================
#endif
//==============================================
