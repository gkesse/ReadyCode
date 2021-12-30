//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
#define GOBJECT GObject::Instance()
#define GRES(x, y) GOBJECT->getResourcePath(x, y)
//===============================================
class GXml;
//===============================================
class GObject {
public:
    GObject();
    ~GObject();
    static GObject* Instance();
    std::string getDataPath() const;
    std::string getResourcePath(const std::string& _resource, const std::string& _filename) const;

private:
    static GObject* m_instance;

protected:
    std::shared_ptr<GXml> m_dom;
};
//==============================================
#endif
//==============================================
