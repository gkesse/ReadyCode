//================================================
#ifndef _GDBusAdaptor_
#define _GDBusAdaptor_
//================================================
#include <QtDBus/QtDBus>
//================================================
class GDBusAdaptor : public QDBusAbstractAdaptor {
    Q_OBJECT
    
public:
    GDBusAdaptor(QObject *parent = 0);
    ~GDBusAdaptor();

signals:
    void emitMessage(const QString& key, const QString& value);
};
//================================================
#endif
//================================================