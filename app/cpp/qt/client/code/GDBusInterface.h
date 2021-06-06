//================================================
#ifndef _GDBusInterface_
#define _GDBusInterface_
//================================================
#include <QtDBus/QtDBus>
//================================================
class GDBusInterface : public QDBusAbstractInterface {
    Q_OBJECT

public:
    GDBusInterface(const QString &service, const QString &path, const QDBusConnection &connection = QDBusConnection::sessionBus(), QObject *parent = 0);
    ~GDBusInterface();

signals:
    void emitDBusMessage(const QString& key, const QString& value);
};
//================================================
#endif
//================================================