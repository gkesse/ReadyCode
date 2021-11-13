//===============================================
#include "GSocket.h"
//===============================================
GSocket::GSocket(QObject* _parent) :
GObject(_parent) {
    m_tcpServer = 0;
    m_tcpSocket = 0;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::server() {
    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}
//===============================================
void GSocket::socket() {
    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}
//===============================================
void GSocket::listen(const QHostAddress& _address, int _port) {
    m_tcpServer->listen(_address, _port);
}
//===============================================
void GSocket::address() {
    QList<QHostAddress> lAddressMap = QNetworkInterface::allAddresses();
    for (int i = 0; i < lAddressMap.size(); ++i) {
        QHostAddress lHostAddress = lAddressMap.at(i);
        QString lAddress = lHostAddress.toString();
        qDebug() << lAddress;
    }
}
//===============================================
void GSocket::accept() {
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}
//===============================================
void GSocket::connects(const QHostAddress& _address, int _port) {
    m_tcpSocket->abort();
    m_tcpSocket->connectToHost(_address, _port);
}
//===============================================
void GSocket::disconnect() {
    m_tcpSocket->disconnectFromHost();
}
//===============================================
void GSocket::write(const QString& _data) {
    QByteArray lData;
    QDataStream lStreamOut(&lData, QIODevice::WriteOnly);
    lStreamOut.setVersion(QDataStream::Qt_5_10);
    lStreamOut << _data;
    m_tcpSocket->write(lData);
}
//===============================================
void GSocket::read(QString& _data) {
    QDataStream lStreamIn;
    lStreamIn.setDevice(m_tcpSocket);
    lStreamIn.setVersion(QDataStream::Qt_5_10);
    lStreamIn.startTransaction();
    lStreamIn >> _data;
    lStreamIn.commitTransaction();
}
//===============================================
void GSocket::onNewConnection() {
    emit onEmit("new_connection");
}
//===============================================
void GSocket::onConnected() {
    emit onEmit("connect");
}
//===============================================
void GSocket::onDisconnected() {
    m_tcpSocket->deleteLater();
    emit onEmit("disconnect");
}
//===============================================
void GSocket::onReadyRead() {
    emit onEmit("ready_read");
}
//===============================================
