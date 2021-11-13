//===============================================
#include "GSocketServer.h"
#include "GSocket.h"
#include "GStruct.h"
//===============================================
GSocketServer::GSocketServer(QObject* _parent) :
GSocketUi(_parent) {

}
//===============================================
GSocketServer::~GSocketServer() {

}
//===============================================
void GSocketServer::run(int _argc, char** _argv) {
    QApplication lApp(_argc, _argv);
    GSocket lServer;
    sGSocket lParams;
    printf("Demarrage du serveur...\n");
    lServer.server();
    lServer.listen(lParams.address, lParams.port);
    connect(&lServer, SIGNAL(onEmit(QString)), this, SLOT(onEvent(QString)));
    lApp.exec();
}
//===============================================
void GSocketServer::onEvent(const QString& _text) {
    if(_text == "new_connection") {
        GSocket* lServer = qobject_cast<GSocket*>(sender());
        lServer->accept();
    }
    else if(_text == "ready_read") {
        GSocket* lServer = qobject_cast<GSocket*>(sender());
        QString lData;
        lServer->read(lData);
        qDebug() << lData;
        lServer->write("OK");
    }
    else if(_text == "disconnect") {
        GSocket* lServer = qobject_cast<GSocket*>(sender());
        lServer->disconnect();
    }
}
//===============================================
