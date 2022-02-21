//===============================================
#include "GXml.h"
//===============================================
static GXmlO* m_GXmlO = 0;
//===============================================
static void GXml_delete(GXmlO* _obj);
static void GXml_init(GXmlO* _obj);
static void GXml_clean(GXmlO* _obj);
//===============================================
static int GXml_loadXmlFile(GXmlO* _obj, const char* _filename);
static void GXml_loadXmlData(GXmlO* _obj, char* _source, int _size);
static int GXml_saveXmlFile(GXmlO* _obj, const char* _filename, const char* _encoding);
static GXmlO* GXml_createDoc(GXmlO* _obj, const char* _root);
static GXmlO* GXml_createDtd(GXmlO* _obj, const char* _root, const char* _filename);
static GXmlO* GXml_createNode(GXmlO* _obj, GXmlO* _node, const char* _name, const char* _content);
static GXmlO* GXml_getRoot(GXmlO* _obj, const char* _nodename);
static GXmlO* GXml_getNode(GXmlO* _obj, const char* _nodename);
static GXmlO* GXml_getNodePtr(GXmlO* _obj, GXmlO* _node);
static GXmlO* GXml_getNodeNext(GXmlO* _obj, GXmlO* _node);
static int GXml_getNodeType(GXmlO* _obj);
static GXmlO* GXml_getNodeChildren(GXmlO* _obj, GXmlO* _node);
static GXmlO* GXml_getNodeEmpty(GXmlO* _obj, const char* _nodename);
static GXmlO* GXml_getNodeIndex(GXmlO* _obj, const char* _nodename, int _index);
static const char* GXml_getNodeName(GXmlO* _obj);
static char* GXml_getNodeValue(GXmlO* _obj);
static char* GXml_getNodeXml(GXmlO* _obj);
static int GXml_isNodeEmpty(GXmlO* _obj);
static int GXml_countNode(GXmlO* _obj, const char* _nodename);
//===============================================
GXmlO* GXml_new() {
    GObjectO* lParent = GObject_new();
    GXmlO* lChild = (GXmlO*)malloc(sizeof(GXmlO));

    lChild->parent = lParent;
    lChild->delete = GXml_delete;
    lChild->init = GXml_init;
    lChild->clean = GXml_clean;
    //
    lChild->loadXmlFile = GXml_loadXmlFile;
    lChild->loadXmlData = GXml_loadXmlData;
    lChild->saveXmlFile = GXml_saveXmlFile;
    lChild->createDoc = GXml_createDoc;
    lChild->createDtd = GXml_createDtd;
    lChild->createNode = GXml_createNode;
    lChild->getRoot = GXml_getRoot;
    lChild->getNode = GXml_getNode;
    lChild->getNodePtr = GXml_getNodePtr;
    lChild->getNodeNext = GXml_getNodeNext;
    lChild->getNodeType = GXml_getNodeType;
    lChild->getNodeChildren = GXml_getNodeChildren;
    lChild->getNodeEmpty = GXml_getNodeEmpty;
    lChild->getNodeIndex = GXml_getNodeIndex;
    lChild->getNodeName = GXml_getNodeName;
    lChild->getNodeValue = GXml_getNodeValue;
    lChild->getNodeXml = GXml_getNodeXml;
    lChild->isNodeEmpty = GXml_isNodeEmpty;
    lChild->countNode = GXml_countNode;
    //
    lChild->m_doc = 0;
    lChild->m_node = 0;
    lChild->m_dtd = 0;
    //
    lParent->child = lChild;

    return lChild;
}
//===============================================
static void GXml_delete(GXmlO* _obj) {
    xmlFreeDoc(_obj->m_doc);
    GObject_delete(_obj->parent);
}
//===============================================
static void GXml_init(GXmlO* _obj) {

}
//===============================================
static void GXml_clean(GXmlO* _obj) {
    xmlCleanupParser();
    xmlMemoryDump();
}
//===============================================
GXmlO* GXml() {
    if(m_GXmlO == 0) {
        m_GXmlO = GXml_new();
    }
    return m_GXmlO;
}
//===============================================
static int GXml_loadXmlFile(GXmlO* _obj, const char* _filename) {
    GObjectO* lObj = _obj->parent;
    char* lFilename = lObj->getRepoPath(lObj, "c/xml", _filename);
    _obj->m_doc = xmlReadFile(lFilename, 0, 0);
    if(!_obj->m_doc) {
        return 0;
    }
    return 1;
}
//===============================================
static void GXml_loadXmlData(GXmlO* _obj, char* _source, int _size) {

}
//===============================================
static int GXml_saveXmlFile(GXmlO* _obj, const char* _filename, const char* _encoding) {
    const char* lFilename = _obj->m_filename;
    const char* lEncoding = "UTF-8";
    if(_filename) lFilename = _filename;
    if(_encoding) lEncoding = _encoding;
    int lOk = xmlSaveFormatFileEnc(lFilename, _obj->m_doc, lEncoding, 1);
    if(lOk == -1) return 0;
    return 1;
}
//===============================================
static GXmlO* GXml_createDoc(GXmlO* _obj, const char* _root) {
    _obj->m_doc = xmlNewDoc(BAD_CAST("1.0"));
    _obj->m_node = xmlNewNode(NULL, BAD_CAST(_root));
    xmlDocSetRootElement(_obj->m_doc, _obj->m_node);
    return _obj;
}
//===============================================
static GXmlO* GXml_createDtd(GXmlO* _obj, const char* _root, const char* _filename) {
    GObjectO* lObj = _obj->parent;
    char* lFilename = lObj->getRepoPath(lObj, "c/xml", _filename);
    if(!_obj->m_doc) return _obj;
    _obj->m_dtd = xmlCreateIntSubset(_obj->m_doc, BAD_CAST(_root), NULL, BAD_CAST(lFilename));
    return _obj;
}
//===============================================
static GXmlO* GXml_createNode(GXmlO* _obj, GXmlO* _node, const char* _name, const char* _content) {
    if(!_obj->m_node) return _obj;
    _node->m_node = xmlNewChild(_obj->m_node, 0, BAD_CAST(_name), BAD_CAST(_content));
    return _obj;
}
//===============================================
static GXmlO* GXml_getRoot(GXmlO* _obj, const char* _nodename) {
    _obj->m_node = xmlDocGetRootElement(_obj->m_doc);
    if(strcmp(_obj->m_node->name, _nodename)) {
        _obj->m_node = 0;
    }
    return _obj;
}
//===============================================
static GXmlO* GXml_getNode(GXmlO* _obj, const char* _nodename) {
    return _obj;
}
//===============================================
static GXmlO* GXml_getNodePtr(GXmlO* _obj, GXmlO* _node) {
    _node->m_node = _obj->m_node;
    return _obj;
}
//===============================================
static GXmlO* GXml_getNodeNext(GXmlO* _obj, GXmlO* _node) {
    if(!_obj->m_node) {
        _node->m_node = 0;
        return _obj;
    }
    _node->m_node = _obj->m_node->next;
    return _obj;
}
//===============================================
static int GXml_getNodeType(GXmlO* _obj) {
    if(!_obj->m_node) return 0;
    return _obj->m_node->type;
}
//===============================================
static GXmlO* GXml_getNodeChildren(GXmlO* _obj, GXmlO* _node) {
    if(!_obj->m_node) {
        _node->m_node = 0;
        return _obj;
    }
    _node->m_node = _obj->m_node->children;
    return _obj;
}
//===============================================
static GXmlO* GXml_getNodeEmpty(GXmlO* _obj, const char* _nodename) {
    return _obj;
}
//===============================================
static GXmlO* GXml_getNodeIndex(GXmlO* _obj, const char* _nodename, int _index) {
    return _obj;
}
//===============================================
static const char* GXml_getNodeName(GXmlO* _obj) {
    if(!_obj->m_node) return "";
    return _obj->m_node->name;
}
//===============================================
static char* GXml_getNodeValue(GXmlO* _obj) {
    return "";
}
//===============================================
static char* GXml_getNodeXml(GXmlO* _obj) {
    return "";
}
//===============================================
static int GXml_isNodeEmpty(GXmlO* _obj) {
    if(!_obj->m_node) return 1;
    return 0;
}
//===============================================
static int GXml_countNode(GXmlO* _obj, const char* _nodename) {
    return 0;
}
//===============================================
