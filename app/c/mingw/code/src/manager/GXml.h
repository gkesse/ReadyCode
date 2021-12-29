//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GXmlO GXmlO;
//===============================================
struct _GXmlO {
    void (*loadXmlFile)(GObjectO* _obj, const char* _filename);
    void (*loadXmlData)(GObjectO* _obj, char* _source, int _size);
    GXmlO* (*getRoot)(GObjectO* _obj, const char* _nodename);
    GXmlO* (*getNode)(GObjectO* _obj, const char* _nodename);
    GXmlO* (*getNodeEmpty)(GObjectO* _obj, const char* _nodename);
    GXmlO* (*getNodeIndex)(GObjectO* _obj, const char* _nodename, int _index);
    char* (*getNodeName)(GObjectO* _obj);
    char* (*getNodeValue)(GObjectO* _obj);
    int (*countNode)(GObjectO* _obj, const char* _nodename);
    //
    struct xml_document* m_doc;
    struct xml_node* m_node;
    char m_nodeName[256];
    char m_nodeValue[1024];
};
//===============================================
GObjectO* GXml_New();
//===============================================
#endif
//===============================================
