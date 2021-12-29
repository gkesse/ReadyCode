//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
//===============================================
class GObject {
public:
    GObject();
    ~GObject();
    std::string getDataPath() const;
    std::string getResourcePath(const std::string& _resource, const std::string& _filename) const;
    std::string getXmlPath(const std::string& _filename) const;

protected:
    std::shared_ptr<GXml> m_dom;
};
//==============================================
#endif
//==============================================
