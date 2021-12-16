//===============================================
#ifndef _GQtObject_
#define _GQtObject_
//===============================================
#include "GInclude.h"
//===============================================
class GQtObject : public QObject {
    Q_OBJECT

public:
    GQtObject(QObject* _parent = 0);
    ~GQtObject();
    QString getDataPath();

private:
    QString m_dataPath;
};
//==============================================
#endif
//==============================================
