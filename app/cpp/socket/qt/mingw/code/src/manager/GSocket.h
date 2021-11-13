//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
class GSocket : public GObject {
    Q_OBJECT

public:
    GSocket(QObject* _parent = 0);
    ~GSocket();
    void server();
    void socket();
    void listen(const QHostAddress& _address, int _port);
    void address();
    void accept();
    void connects(const QHostAddress& _address, int _port);
    void disconnect();
    void write(const QString& _data);
    void read(QString& _data);

public slots:
    void onNewConnection();
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;
};
//==============================================
#endif
//==============================================
