//===============================================
#include "GXml.h"
//===============================================
static void GXml_delete(GXml* _this);
static void GXml_clean(GXml* _this);
static void GXml_init(GXml* _this);
static void GXml_loadFile(GXml* _this, const char* _filename);
static void GXml_print(GXml* _this);
//===============================================
GXml* GXml_new() {
    GXml* lObj = (GXml*)malloc(sizeof(GXml));
    lObj->m_parent = GObject_new();
    lObj->m_doc = 0;

    lObj->delete = GXml_delete;
    lObj->clean = GXml_clean;
    lObj->init = GXml_init;
    lObj->loadFile = GXml_loadFile;
    lObj->print = GXml_print;
    return lObj;
}
//===============================================
static void GXml_delete(GXml* _this) {
    assert(_this);
    _this->m_parent->delete(_this->m_parent);
    xmlFreeDoc(_this->m_doc);
    free(_this);
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
static void GXml_loadFile(GXml* _this, const char* _filename) {
    assert(_this);
    _this->m_doc = xmlParseFile(_filename);
}
//===============================================
static void GXml_print(GXml* _this) {
    assert(_this);
    assert(_this->m_doc);
    xmlSaveFormatFileEnc("-", _this->m_doc, "UTF-8", 1);
}
//===============================================
