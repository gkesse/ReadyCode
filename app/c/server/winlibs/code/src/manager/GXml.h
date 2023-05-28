//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GXml GXml;
//===============================================
struct _GXml {
    GLog* m_logs;
    xmlDocPtr m_doc;
    xmlNodePtr m_node;

    void (*delete)(GXml* _this);
    void (*clear)(GXml* _this);
    void (*clean)(GXml* _this);
    void (*init)(GXml* _this);
    void (*createDoc)(GXml* _this);
    xmlNodePtr (*createNode)(GXml* _this, GXml* _root, const char* _path, const char* _value);
    int (*existeNode)(GXml* _this, GXml* _root, const char* _path);
    xmlNodePtr (*getNode)(GXml* _this, GXml* _root, const char* _path);
    int (*countNode)(GXml* _this, GXml* _root, const char* _path);
    xmlNodePtr (*addData)(GXml* _this, const char* _key, const char* _value);
    xmlNodePtr (*addObj)(GXml* _this, const char* _key);
    void (*setValue)(GXml* _this, const char* _value);
    const char* (*getValue)(GXml* _this);
    int (*loadFile)(GXml* _this, const char* _filename);
    int (*loadXml)(GXml* _this, const char* _data);
    GString* (*toString)(GXml* _this);
    GString* (*toNode)(GXml* _this, GXml* _root);
    void (*loadNode)(GXml* _this, const char* _data);
    void (*print)(GXml* _this);
};
//===============================================
GXml* GXml_new();
//===============================================
#endif
//===============================================
