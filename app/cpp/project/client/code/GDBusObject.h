//================================================
#ifndef _GDBusObject_
#define _GDBusObject_
//================================================
#include <QApplication>
#include <QtDBus/QtDBus>
//================================================
class GDBusObject : public QObject {
    Q_OBJECT
    
public:
    GDBusObject(QObject* parent = 0);
    ~GDBusObject();
};
//================================================
#endif
//================================================