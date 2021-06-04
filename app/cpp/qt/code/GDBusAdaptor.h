//================================================
#ifndef _GDBusAdaptor_
#define _GDBusAdaptor_
//================================================
#include <QtDBus/QtDBus>
//================================================
class GDBusAdaptor : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.readydev.app")
    Q_CLASSINFO("D-Bus Introspection", ""
    "<interface name=\"com.readydev.app\">\n"
    "   <signal name=\"emitDBusMessage\">\n"
    "       <arg direction=\"out\" type=\"s\" name=\"key\"/>\n"
    "       <arg direction=\"out\" type=\"s\" name=\"value\"/>\n"
    "    </signal>\n"
    "</interface>\n"
    "")
        
public:
    GDBusAdaptor(QObject *parent = 0);
    ~GDBusAdaptor();

signals:
    void emitDBusMessage(const QString& key, const QString& value);
};
//================================================
#endif
//================================================