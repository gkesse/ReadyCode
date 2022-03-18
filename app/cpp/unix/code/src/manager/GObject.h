//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
class GCode;
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    virtual std::string getItem(const std::string& _code, const std::string& _data) const;

protected:
    std::shared_ptr<GXml> m_dom;
    std::shared_ptr<GCode> m_res;
};
//===============================================
#endif
//===============================================
