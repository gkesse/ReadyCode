//===============================================
#ifndef _GPath2_
#define _GPath2_
//===============================================
#include "GObject2.h"
//===============================================
#define GPATHI2 GPath2::Instance()
#define GPATH   GPATHI2->getResourcePath
//===============================================
class GPath2 : public GObject2 {
	Q_OBJECT

public:
    GPath2(QObject* _parent = 0);
    ~GPath2();
    static GPath2* Instance();
    GString getDataPath() const;
    GString getResourcePath(const GString& _res, const GString& _filename) const;

private:
    static GPath2* m_instance;
};
//==============================================
#endif
//==============================================
