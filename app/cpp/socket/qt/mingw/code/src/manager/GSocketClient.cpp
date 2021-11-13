//===============================================
#include "GSocketClient.h"
#include "GSocket.h"
#include "GStruct.h"
//===============================================
GSocketClient::GSocketClient(QObject* _parent) :
GSocketUi(_parent) {

}
//===============================================
GSocketClient::~GSocketClient() {

}
//===============================================
void GSocketClient::run(int _argc, char** _argv) {
    QApplication lApp(_argc, _argv);
    GSocket lClient;
    sGSocket lParams;
    lParams.address = "127.0.0.1";
    lClient.socket();
    connect(&lClient, SIGNAL(onEmit(QString)), this, SLOT(onEvent(QString)));
    lClient.connects(lParams.address, lParams.port);
    lApp.exec();
}
//===============================================
void GSocketClient::onEvent(const QString& _text) {
    if(_text == "connect") {
        GSocket* lClient = qobject_cast<GSocket*>(sender());
        lClient->write("Bonjour tout le monde");
    }
    else if(_text == "ready_read") {
        GSocket* lClient = qobject_cast<GSocket*>(sender());
        QString lData;
        lClient->read(lData);
        qDebug() << lData;
        qApp->quit();
    }
}
//===============================================
