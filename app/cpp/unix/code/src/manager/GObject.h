//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
#define GOBJ_ERR_ADD(...) m_errors->addError(sformat(__VA_ARGS__))
#define GOBJ_ERR_GET(x) x.getErrors()->toString().c_str()
//===============================================
class GXml;
class GCode;
class GError;
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    std::shared_ptr<GXml>& getDom();
    std::shared_ptr<GError>& getErrors();

protected:
    std::shared_ptr<GXml> m_dom;
    std::shared_ptr<GCode> m_res;
    std::shared_ptr<GError> m_errors;
};
//===============================================
#endif
//===============================================
