//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
//===============================================
class GSocket {
public:
    GSocket();
    ~GSocket();
    static GSocket* Instance();
    //
    void createDoms();
    QString getItem(const QString& _key, const QString& _data) const;
    int loadDomain() const;
    int loadType() const;
    int loadProtocol() const;
    int loadFamily() const;
    //
    GSocket& initSocket(int _major, int _minor);
    GSocket& createSocket(int _domain, int _type, int _protocol);
    GSocket& createAddress(int _family, const QString& _addressIp, int _port);
    GSocket& listenSocket(int _backlog);
    GSocket& bindSocket();
    GSocket& connectSocket();
    void startMessage();
    GSocket& acceptSocket(GSocket& _socket);
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

private:
    QSharedPointer<GXml> m_dom;
    //
    static const int BUFFER_DATA_SIZE = 1024;
    static const int BUFFER_HOSTNAME_SIZE = 256;
    //
    SOCKET m_socket;
    SOCKADDR_IN m_address;
};
//==============================================
#endif
//==============================================
