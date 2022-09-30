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
public:
    GPath();
    ~GPath();
    static GPath* Instance();
    GString getPath() const;
    GString getResourcePath(const GString& _res, const GString& _filename) const;

private:
    static GPath* m_instance;
};
//==============================================
#endif
//==============================================
