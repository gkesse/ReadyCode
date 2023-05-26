//===============================================
#include "GXml.h"
//===============================================
static void GXml_delete(GXml* _this);
static void GXml_deleteObj(GXml* _this);
static void GXml_clear(GXml* _this);
static void GXml_clean(GXml* _this);
static void GXml_init(GXml* _this);
static void GXml_createDoc(GXml* _this);
static GXml* GXml_addData(GXml* _this, const char* _key, const char* _value);
static GXml* GXml_addObj(GXml* _this, const char* _key);
static void GXml_setNext(GXml* _this, GXml* _node);
static void GXml_loadFile(GXml* _this, const char* _filename);
static void GXml_print(GXml* _this);
//===============================================
GXml* GXml_new() {
    GXml* lObj = (GXml*)malloc(sizeof(GXml));
    lObj->m_logs = GLog_new();
    lObj->m_doc = 0;
    lObj->m_node = 0;
    lObj->m_next = 0;

    lObj->delete = GXml_delete;
    lObj->deleteObj = GXml_deleteObj;
    lObj->clear = GXml_clear;
    lObj->clean = GXml_clean;
    lObj->init = GXml_init;
    lObj->createDoc = GXml_createDoc;
    lObj->addData = GXml_addData;
    lObj->addObj = GXml_addObj;
    lObj->setNext = GXml_setNext;
    lObj->loadFile = GXml_loadFile;
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
static void GXml_deleteObj(GXml* _this) {
    assert(_this);
    GXml* lNode = _this->m_next;
    while(1) {
        if(!lNode) break;
        GXml* lPrevious = lNode;
        lNode = lNode->m_next;
        lPrevious->m_logs->delete(lPrevious->m_logs);
        free(lPrevious);
    }
    _this->m_next = 0;
}
//===============================================
static void GXml_clear(GXml* _this) {
    assert(_this);
    _this->deleteObj(_this);
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
static GXml* GXml_addData(GXml* _this, const char* _key, const char* _value) {
    assert(_this);
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_key));
    xmlNodeSetContent(lNode, BAD_CAST(_value));
    xmlAddChild(_this->m_node, lNode);
    return _this;
}
//===============================================
static GXml* GXml_addObj(GXml* _this, const char* _key) {
    assert(_this);
    GXml* lNode = GXml_new();
    lNode->m_node = xmlNewNode(NULL, BAD_CAST(_key));
    xmlAddChild(_this->m_node, lNode->m_node);
    _this->setNext(_this, lNode);
    return lNode;
}
//===============================================
static void GXml_setNext(GXml* _this, GXml* _node) {
    assert(_this);
    GXml* lNode = _this;
    while(1) {
        if(!lNode->m_next) break;
        lNode = lNode->m_next;
    }
    lNode->m_next = _node;
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
