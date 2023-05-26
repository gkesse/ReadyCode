//===============================================
#ifndef _GCode_
#define _GCode_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GCode GCode;
typedef struct _GXml GXml;
//===============================================
struct _GCode {
    GXml* m_dom;

    void (*delete)(GCode* _this);
    void (*createRequest)(GCode* _this, const char* _module, const char* _method);
};
//===============================================
GCode* GCode_new();
//===============================================
#endif
//===============================================
