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
    xmlNodePtr m_node;
    GXml* m_next;

    void (*delete)(GXml* _this);
    void (*deleteObj)(GXml* _this);
    void (*clear)(GXml* _this);
    void (*clean)(GXml* _this);
    void (*init)(GXml* _this);
    void (*createDoc)(GXml* _this);
    GXml* (*addData)(GXml* _this, const char* _key, const char* _value);
    GXml* (*addObj)(GXml* _this, const char* _key);
    void (*setNext)(GXml* _this, GXml* _node);
    void (*loadFile)(GXml* _this, const char* _filename);
    void (*print)(GXml* _this);
};
//===============================================
GXml* GXml_new();
//===============================================
#endif
//===============================================
