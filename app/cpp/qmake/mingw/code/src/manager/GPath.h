//===============================================
#ifndef _GPath_
#define _GPath_
//===============================================
#include "GObject.h"
//===============================================
#define GPATHI  GPath::Instance()
#define GPATH   GPATHI->getResourcePath
//===============================================
class GPath : public GObject {
public:
    GPath();
    ~GPath();
    static GPath* Instance();
    void initPath();
    GString getDataPath() const;
    GString getResourcePath(const GString& _res, const GString& _filename) const;

private:
    static GPath* m_instance;
    GString m_dataPath;
};
//==============================================
#endif
//==============================================
