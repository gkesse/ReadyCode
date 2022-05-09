//===============================================
#ifndef _GQtObject_
#define _GQtObject_
//===============================================
#include "GInclude.h"
//===============================================
#define GQTOBJECT GQtObject::Instance()
#define GQTRES(x, y) GQTOBJECT->getResourcePath(x, y)
#define GQTSTYLE(x) GQTOBJECT->setStylesheet(x)
//===============================================
class GQtObject : public QObject {
    Q_OBJECT

public:
    GQtObject(QObject* _parent = 0);
    virtual ~GQtObject();
    static GQtObject* Instance();
    QString getDataPath();
    QString getResourcePath(const QString& _resource, const QString& _filename);
    bool setStylesheet(const QString& _filename);

private:
    static GQtObject* m_instance;
};
//==============================================
#endif
//==============================================
