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

protected:
    std::shared_ptr<GXml> m_dom;
};
//===============================================
#endif
//===============================================
