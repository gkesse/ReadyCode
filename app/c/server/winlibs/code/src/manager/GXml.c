//===============================================
#include "GXml.h"
#include "GVector.h"
//===============================================
static void GXml_delete(GXml* _this);
static void GXml_clear(GXml* _this);
static void GXml_clean(GXml* _this);
static void GXml_init(GXml* _this);
static void GXml_createDoc(GXml* _this);
static xmlNodePtr GXml_createNode(GXml* _this, GXml* _root, const char* _path, const char* _value);
static int GXml_existeNode(GXml* _this, GXml* _root, const char* _path);
static xmlNodePtr GXml_getNode(GXml* _this, GXml* _root, const char* _path);
static int GXml_countNode(GXml* _this, GXml* _root, const char* _path);
static xmlNodePtr GXml_addData(GXml* _this, const char* _key, const char* _value);
static xmlNodePtr GXml_addObj(GXml* _this, const char* _key);
static void GXml_setValue(GXml* _this, const char* _value);
static const char* GXml_getValue(GXml* _this);
static int GXml_loadFile(GXml* _this, const char* _filename);
static int GXml_loadXml(GXml* _this, const char* _data);
static GString* GXml_toString(GXml* _this);
static GString* GXml_toNode(GXml* _this, GXml* _root);
static void GXml_loadNode(GXml* _this, const char* _data);
static void GXml_print(GXml* _this);
//===============================================
GXml* GXml_new() {
    GXml* lObj = (GXml*)malloc(sizeof(GXml));
    lObj->m_logs = GLog_new();
    lObj->m_doc = 0;
    lObj->m_node = 0;

    lObj->delete = GXml_delete;
    lObj->clear = GXml_clear;
    lObj->clean = GXml_clean;
    lObj->init = GXml_init;
    lObj->createDoc = GXml_createDoc;
    lObj->createNode = GXml_createNode;
    lObj->existeNode = GXml_existeNode;
    lObj->getNode = GXml_getNode;
    lObj->countNode = GXml_countNode;
    lObj->addData = GXml_addData;
    lObj->addObj = GXml_addObj;
    lObj->setValue = GXml_setValue;
    lObj->getValue = GXml_getValue;
    lObj->loadFile = GXml_loadFile;
    lObj->loadXml = GXml_loadXml;
    lObj->toString = GXml_toString;
    lObj->toNode = GXml_toNode;
    lObj->loadNode = GXml_loadNode;
    lObj->print = GXml_print;
    return lObj;
}
//===============================================
static void GXml_delete(GXml* _this) {
    assert(_this);
    _this->m_logs->delete(_this->m_logs);
    _this->clear(_this);
    free(_this);
}
//===============================================
static void GXml_clear(GXml* _this) {
    assert(_this);
    xmlFreeDoc(_this->m_doc);
}
//===============================================
static void GXml_clean(GXml* _this) {
    assert(_this);
    xmlCleanupParser();
    xmlMemoryDump();
}
//===============================================
static void GXml_init(GXml* _this) {
    assert(_this);
    xmlInitParser();
    xmlKeepBlanksDefault(0);
}
//===============================================
static void GXml_createDoc(GXml* _this) {
    assert(_this);
    _this->clear(_this);
    _this->m_doc = xmlNewDoc(BAD_CAST("1.0"));
    _this->m_node = xmlNewNode(NULL, BAD_CAST("rdv"));
    xmlDocSetRootElement(_this->m_doc, _this->m_node);
}
//===============================================
static xmlNodePtr GXml_createNode(GXml* _this, GXml* _root, const char* _path, const char* _value) {
    assert(_this);
    GString* lString = GString_new();
    GString* lPath = GString_new();
    GVector* lMap = lString->split(lString, _path, "/");
    GXml* lNode = GXml_new();
    lNode->m_node = _this->m_node;

    if(_path[0] == '/') lPath->add(lPath, "/");

    for(int i = 0; i < lMap->size(lMap); i++) {
        GString* lData = lMap->get(lMap, i);
        if(i != 0) lPath->add(lPath, "/");
        lPath->add(lPath, lData->m_data);
        if(!_this->existeNode(_this, _root, lPath->m_data)) {
            lNode->m_node = _this->addObj(lNode, lData->m_data);
        }
        else {
            lNode->m_node = _this->getNode(_this, _root, lPath->m_data);
        }
        lData->delete(lData);
    }
    xmlNodePtr lNodeC = lNode->m_node;

    if(strcmp(_value, "")) {
        xmlNodeSetContent(lNodeC, BAD_CAST(_value));
    }

    lMap->delete(lMap);
    lNode->delete(lNode);
    lString->delete(lString);
    lPath->delete(lPath);
    return lNodeC;
}
//===============================================
static int GXml_existeNode(GXml* _this, GXml* _root, const char* _path) {
    assert(_this);
    assert(_root);
    assert(_root->m_doc);
    xmlXPathContextPtr lXPathC = xmlXPathNewContext(_root->m_doc);
    assert(lXPathC);
    xmlNodePtr lRoot = _this->m_node;
    if(_path[0] == '/') lRoot = _root->m_node;
    xmlXPathObjectPtr lXPathO = xmlXPathNodeEval(lRoot, BAD_CAST(_path), lXPathC);
    assert(lXPathO);
    xmlXPathFreeContext(lXPathC);
    int lExistOk = 0;
    if(lXPathO->nodesetval) {
        if(lXPathO->nodesetval->nodeNr) lExistOk = 1;
    }
    xmlXPathFreeObject(lXPathO);
    return lExistOk;
}
//===============================================
static xmlNodePtr GXml_getNode(GXml* _this, GXml* _root, const char* _path) {
    assert(_this);
    assert(_root);
    assert(_root->m_doc);
    xmlXPathContextPtr lXPathC = xmlXPathNewContext(_root->m_doc);
    assert(lXPathC);
    xmlNodePtr lRoot = _this->m_node;
    if(_path[0] == '/') lRoot = _root->m_node;
    xmlXPathObjectPtr lXPathO = xmlXPathNodeEval(lRoot, BAD_CAST(_path), lXPathC);
    assert(lXPathO);
    xmlXPathFreeContext(lXPathC);
    xmlNodePtr lNode = 0;
    if(lXPathO->nodesetval) {
        if(lXPathO->nodesetval->nodeNr) {
            lNode = lXPathO->nodesetval->nodeTab[0];
        }
    }
    xmlXPathFreeObject(lXPathO);
    return lNode;
}
//===============================================
static int GXml_countNode(GXml* _this, GXml* _root, const char* _path) {
    assert(_this);
    assert(_root);
    assert(_root->m_doc);
    xmlXPathContextPtr lXPathC = xmlXPathNewContext(_root->m_doc);
    assert(lXPathC);
    xmlNodePtr lRoot = _this->m_node;
    if(_path[0] == '/') lRoot = _root->m_node;
    xmlXPathObjectPtr lXPathO = xmlXPathNodeEval(lRoot, BAD_CAST(_path), lXPathC);
    assert(lXPathO);
    xmlXPathFreeContext(lXPathC);
    int lCount = 0;
    if(lXPathO->nodesetval) {
        lCount = lXPathO->nodesetval->nodeNr;
    }
    xmlXPathFreeObject(lXPathO);
    return lCount;
}
//===============================================
static xmlNodePtr GXml_addData(GXml* _this, const char* _key, const char* _value) {
    assert(_this);
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_key));
    xmlNodeSetContent(lNode, BAD_CAST(_value));
    xmlAddChild(_this->m_node, lNode);
    return _this->m_node;
}
//===============================================
static xmlNodePtr GXml_addObj(GXml* _this, const char* _key) {
    assert(_this);
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_key));
    xmlAddChild(_this->m_node, lNode);
    return lNode;
}
//===============================================
static void GXml_setValue(GXml* _this, const char* _value) {
    assert(_this);
    assert(_this->m_node);
    xmlNodeSetContent(_this->m_node, BAD_CAST(_value));
}
//===============================================
static const char* GXml_getValue(GXml* _this) {
    assert(_this);
    assert(_this->m_node);
    const char* lData = xmlNodeGetContent(_this->m_node);
    return lData;
}
//===============================================
static GString* GXml_toString(GXml* _this) {
    assert(_this);
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(_this->m_doc, &lBuffer, &lSize, "UTF-8", 4);
    GString* lData = GString_new();
    lData->create(lData, lBuffer);
    xmlFree(lBuffer);
    return lData;
}
//===============================================
static GString* GXml_toNode(GXml* _this, GXml* _root) {
    assert(_this);
    GString* lData = GString_new();
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, _root->m_doc, _this->m_node, 0, 1);
    lData->create(lData, (char*)lBuffer->content);
    xmlBufferFree(lBuffer);
    return lData;
}
//===============================================
static void GXml_loadNode(GXml* _this, const char* _data) {
    assert(_this);
    int lSize = strlen(_data);
    xmlNodePtr lNodes;
    xmlParseInNodeContext(_this->m_node, _data, lSize, 0, &lNodes);
    xmlNodePtr lNode = lNodes->children;
    while(lNode) {
        xmlAddChild(_this->m_node, xmlCopyNode(lNode, 1));
        lNode = lNode->next;
    }
    xmlFreeNode(lNodes);
}
//===============================================
static int GXml_loadFile(GXml* _this, const char* _filename) {
    assert(_this);
    _this->clear(_this);
    _this->m_doc = xmlParseFile(_filename);
    if(!_this->m_doc) return 0;
    _this->m_node = xmlDocGetRootElement(_this->m_doc);
    if(!_this->m_node) return 0;
    return 1;
}
//===============================================
static int GXml_loadXml(GXml* _this, const char* _data) {
    assert(_this);
    _this->clear(_this);
    _this->m_doc = xmlParseDoc(_data);
    if(!_this->m_doc) return 0;
    _this->m_node = xmlDocGetRootElement(_this->m_doc);
    if(!_this->m_node) return 0;
    return 1;
}
//===============================================
static void GXml_print(GXml* _this) {
    assert(_this);
    assert(_this->m_doc);
    xmlSaveFormatFileEnc("-", _this->m_doc, "UTF-8", 1);
}
//===============================================
