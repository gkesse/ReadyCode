//===============================================
#ifndef _GList_
#define _GList_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GListO GListO;
//===============================================
struct _GListO {
    void (*loadXmlFile)(GObjectO* _obj, const char* _filename);
    void (*loadXmlData)(GObjectO* _obj, char* _source, int _size);
    GListO* (*getRoot)(GObjectO* _obj, const char* _nodename);
    GListO* (*getNode)(GObjectO* _obj, const char* _nodename);
    char* (*getNodeName)(GObjectO* _obj);
    char* (*getNodeValue)(GObjectO* _obj);
    int (*countNode)(GObjectO* _obj);
    //
    struct xml_document* m_doc;
    struct xml_node* m_node;
    char m_nodeName[256];
    char m_nodeValue[1024];
};
//===============================================
GObjectO* GList_New();
//===============================================
#endif
//===============================================
