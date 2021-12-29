//================================================
#include "GDBusInterface.h"
//================================================
GDBusInterface::GDBusInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent) : 
QDBusAbstractInterface(service, path, "com.readydev.app", connection, parent) {

}
//================================================
GDBusInterface::~GDBusInterface() {

}
//================================================
