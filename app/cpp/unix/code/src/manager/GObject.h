//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
class GCode;
class GError;
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();

protected:
    std::shared_ptr<GXml> m_dom;
    std::shared_ptr<GCode> m_res;
    std::shared_ptr<GError> m_errors;
};
//===============================================
#endif
//===============================================
