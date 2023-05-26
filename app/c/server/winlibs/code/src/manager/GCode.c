//===============================================
#include "GCode.h"
#include "GXml.h"
//===============================================
static void GCode_delete(GCode* _this);
static void GCode_createRequest(GCode* _this, const char* _module, const char* _method);
//===============================================
GCode* GCode_new() {
    GCode* lObj = (GCode*)malloc(sizeof(GCode));
    lObj->m_dom = GXml_new();

    lObj->delete = GCode_delete;
    lObj->createRequest = GCode_createRequest;
    return lObj;
}
//===============================================
static void GCode_delete(GCode* _this) {
    assert(_this);
    _this->m_dom->delete(_this->m_dom);
    free(_this);
}
//===============================================
static void GCode_createRequest(GCode* _this, const char* _module, const char* _method) {
    assert(_this);
    GXml* lDom = _this->m_dom;
    GXml* lObj;

    lDom->createDoc(lDom);
    lDom->addObj(lDom, "data");
}
//===============================================
