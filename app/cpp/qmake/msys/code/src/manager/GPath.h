//===============================================
#ifndef _GPath_
#define _GPath_
//===============================================
#include "GObject.h"
//===============================================
#define GPATH GPath::Instance()
#define GRES(x, y) GPATH->getResourcePath(x, y)
//===============================================
class GPath : public GObject {
	Q_OBJECT

public:
    GPath(QObject* _parent = 0);
    ~GPath();
    static GPath* Instance();
    QString getDataPath() const;
    QString getResourcePath(const QString& _res, const QString& _filename) const;

private:
    static GPath* m_instance;
};
//==============================================
#endif
//==============================================
