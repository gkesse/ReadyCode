//===============================================
#ifndef _GPath_
#define _GPath_
//===============================================
#include "GObject.h"
//===============================================
#define GPATHI  GPath::Instance()
#define GRES    GPATHI->getPath
//===============================================
class GPath : public GObject {
	Q_OBJECT

public:
    GPath(QObject* _parent = 0);
    ~GPath();
    static GPath* Instance();
    QString getDataPath() const;
    QString getPath(const QString& _res, const QString& _filename) const;

private:
    static GPath* m_instance;
};
//==============================================
#endif
//==============================================
