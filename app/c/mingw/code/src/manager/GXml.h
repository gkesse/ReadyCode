//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GXmlO GXmlO;
//===============================================
struct _GXmlO {
    GObjectO* parent;
    //
    void (*delete)(GXmlO** _obj);
    void (*init)(GXmlO* _obj);
    void (*clean)(GXmlO* _obj);
    int (*loadXmlFile)(GXmlO* _obj, const char* _filename);
    void (*loadXmlData)(GXmlO* _obj, char* _source, int _size);
    int (*saveXmlFile)(GXmlO* _obj, const char* _filename, const char* _encoding);
    GXmlO* (*createDoc)(GXmlO* _obj, const char* _root);
    GXmlO* (*createDtd)(GXmlO* _obj, const char* _root, const char* _filename);
    GXmlO* (*createNode)(GXmlO* _obj, GXmlO* _node, const char* _name, const char* _content);
    GXmlO* (*getRoot)(GXmlO* _obj, const char* _nodename);
    GXmlO* (*getNode)(GXmlO* _obj, const char* _nodename);
    GXmlO* (*getNodePtr)(GXmlO* _obj, GXmlO* _node);
    GXmlO* (*getNodeNext)(GXmlO* _obj, GXmlO* _node);
    int (*getNodeType)(GXmlO* _obj);
    GXmlO* (*getNodeChildren)(GXmlO* _obj, GXmlO* _node);
    GXmlO* (*getNodeEmpty)(GXmlO* _obj, const char* _nodename);
    GXmlO* (*getNodeIndex)(GXmlO* _obj, const char* _nodename, int _index);
    const char* (*getNodeName)(GXmlO* _obj);
    char* (*getNodeValue)(GXmlO* _obj);
    char* (*getNodeXml)(GXmlO* _obj);
    int (*isNodeEmpty)(GXmlO* _obj);
    int (*countNode)(GXmlO* _obj, const char* _nodename);
    //
    xmlDoc* m_doc;
    xmlNode* m_node;
    xmlDtd* m_dtd;
    //
    char* m_filename;
    char m_nodeName[256];
    char m_nodeValue[1024];
    char m_nodeXml[1024];
};
//===============================================
GXmlO* GXml_new();
GXmlO* GXml();
//===============================================
#endif
//===============================================
