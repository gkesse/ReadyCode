//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
class GObject : public QObject {
    Q_OBJECT

public:
    GObject(QObject* _parent = 0);
    ~GObject();
    static GObject* Create(const QString& _key, QObject* _parent = 0);

public slots:
    virtual void onEvent();

signals:
    void onEmit(const QString& _text);

protected:
    QMap<QObject*, QString> m_objMap;
};
//==============================================
#endif
//==============================================
