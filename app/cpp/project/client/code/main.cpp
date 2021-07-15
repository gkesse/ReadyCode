//===============================================
#include <QApplication>
#include <QtDBus/QtDBus>
//===============================================
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    if (!QDBusConnection::sessionBus().isConnected()) {
        qDebug() << "[error] connexion bus session";
        return 0;
    }
    QDBusInterface lInterface("com.readydev.app", "/", "", QDBusConnection::sessionBus());
    if (lInterface.isValid()) {
        QDBusReply<QString> lReplyHello = lInterface.call("say_hello");
        if (lReplyHello.isValid()) {
            printf("say_hello : %s\n", qPrintable(lReplyHello.value()));
        }
        QDBusReply<int> lReplyAdd = lInterface.call("add_data", 20, 30);
        if (lReplyAdd.isValid()) {
            printf("add_data : %d\n", lReplyAdd.value());
        }
    }
    return 0;
}
//===============================================