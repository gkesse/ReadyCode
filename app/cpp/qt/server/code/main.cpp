//===============================================
#include "GDBusObject.h"
//===============================================
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    if (!QDBusConnection::sessionBus().isConnected()) {
        qDebug() << "[error] connexion bus session";
        return 0;
    }
    if (!QDBusConnection::sessionBus().registerService("com.readydev.app")) {
        qDebug() << "[error] enregistrement service";
        return 0;
    }
    GDBusObject lObject;
    QDBusConnection::sessionBus().registerObject("/", &lObject, QDBusConnection::ExportAllSlots);    
    return app.exec();
}
//===============================================