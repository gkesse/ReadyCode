//===============================================
#ifndef _GQtResource_
#define _GQtResource_
//===============================================
#include "GQtObject.h"
//===============================================
#define GQTRES GQtResource::Instance()
#define GQTXML(x) GQTRES->getXmlPath(x)
#define GQTIMG(x) GQTRES->getImgPath(x)
//===============================================
class GQtResource : public GQtObject {
public:
    GQtResource(QObject* _parent = 0);
    ~GQtResource();
    static GQtResource* Instance();
    QString getResPath(const QString& _dataPath, const QString& _resPath, const QString& _filename);
    QString getXmlPath(const QString& _filename);
    QString getImgPath(const QString& _filename);

private:
    static GQtResource* m_instance;
};
//==============================================
#endif
//==============================================
