//================================================
#include "GWindow.h"
//================================================
GWindow::GWindow(QWidget* parent) : QFrame(parent) {
    if (!QDBusConnection::sessionBus().isConnected()) {
        qDebug() << "[error] connexion dbus";
        return;
    }


}
//================================================
GWindow::~GWindow() {

}
//================================================
