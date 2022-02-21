//===============================================
#ifndef _GXmlParser_
#define _GXmlParser_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GXmlParserO GXmlParserO;
//===============================================
struct _GXmlParserO {
    void* parent;
    //
    void (*delete)(GXmlParserO* _obj);
    void (*run)(GXmlParserO* _obj, int _argc, char** _argv);
    void (*loadXmlFile)(GXmlParserO* _obj, const char* _filename);
    void (*loadXmlData)(GXmlParserO* _obj, char* _source, int _size);
    void (*createDoc)(GXmlParserO* _obj, const char* _root);
    GXmlParserO* (*getRoot)(GXmlParserO* _obj, const char* _nodename);
    GXmlParserO* (*getNode)(GXmlParserO* _obj, const char* _nodename);
    GXmlParserO* (*getNodeEmpty)(GXmlParserO* _obj, const char* _nodename);
    GXmlParserO* (*getNodeIndex)(GXmlParserO* _obj, const char* _nodename, int _index);
    char* (*getNodeName)(GXmlParserO* _obj);
    char* (*getNodeValue)(GXmlParserO* _obj);
    char* (*getNodeXml)(GXmlParserO* _obj);
    int (*countNode)(GXmlParserO* _obj, const char* _nodename);
    //
    struct xml_document* m_doc;
    struct xml_node* m_node;
    //
    char m_nodeName[256];
    char m_nodeValue[1024];
    char m_nodeXml[1024];
};
//===============================================
GXmlParserO* GXmlParser_new();
//===============================================
#endif
//===============================================
