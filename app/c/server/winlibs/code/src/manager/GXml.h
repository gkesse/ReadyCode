//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GXml GXml;
//===============================================
struct _GXml {
    GObject* m_parent;
    xmlDocPtr m_doc;

    void (*delete)(GXml* _this);
    void (*clean)(GXml* _this);
    void (*init)(GXml* _this);
    void (*loadFile)(GXml* _this, const char* _filename);
    void (*print)(GXml* _this);
};
//===============================================
GXml* GXml_new();
//===============================================
#endif
//===============================================
