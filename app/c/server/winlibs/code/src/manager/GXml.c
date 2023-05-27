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
static xmlNodePtr GXml_addData(GXml* _this, const char* _key, const char* _value);
static xmlNodePtr GXml_addObj(GXml* _this, const char* _key);
static void GXml_setValue(GXml* _this, const char* _value);
static void GXml_loadFile(GXml* _this, const char* _filename);
static GString* GXml_toString(GXml* _this);
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
    lObj->addData = GXml_addData;
    lObj->addObj = GXml_addObj;
    lObj->setValue = GXml_setValue;
    lObj->loadFile = GXml_loadFile;
    lObj->toString = GXml_toString;
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
}
//===============================================
static void GXml_init(GXml* _this) {
    assert(_this);
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
static void GXml_loadFile(GXml* _this, const char* _filename) {
    assert(_this);
    _this->clear(_this);
    _this->m_doc = xmlParseFile(_filename);
}
//===============================================
static void GXml_print(GXml* _this) {
    assert(_this);
    assert(_this->m_doc);
    xmlSaveFormatFileEnc("-", _this->m_doc, "UTF-8", 1);
}
//===============================================
