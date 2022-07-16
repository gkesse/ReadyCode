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
    std::string getPath() const;
    std::string getResourcePath(const std::string& _res, const std::string& _filename) const;

private:
    static GPath* m_instance;
};
//==============================================
#endif
//==============================================
