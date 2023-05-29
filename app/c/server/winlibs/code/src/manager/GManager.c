//===============================================
#include "GManager.h"
#include "GCode.h"
//===============================================
static void GManager_delete(GManager* _this);
static GObject* GManager_clone(GObject* _this);
static GString* GManager_serialize(GObject* _this);
static void GManager_deserialize(GObject* _this, const char* _data);
//===============================================
GManager* GManager_new() {
    GManager* lObj = (GManager*)malloc(sizeof(GManager));
    lObj->m_parent = GObject_new();
    lObj->m_module = "";
    lObj->m_method = "";

    lObj->delete = GManager_delete;

    lObj->m_parent->clone = GManager_clone;
    lObj->m_parent->serialize = GManager_serialize;
    lObj->m_parent->deserialize = GManager_deserialize;
    lObj->m_parent->m_child = lObj;
    return lObj;
}
//===============================================
static void GManager_delete(GManager* _this) {
    assert(_this);
    _this->m_parent->delete(_this->m_parent);
    free(_this);
}
//===============================================
static GObject* GManager_clone(GObject* _this) {
    assert(_this);
    return GManager_new()->m_parent;
}
//===============================================
static GString* GManager_serialize(GObject* _this) {
    assert(_this);
    const char* lCode = "manager";
    GCode* lDom = GCode_new();
    GString* lData = GString_new();
    lDom->m_dom->createDoc(lDom->m_dom);
    GManager* lObj = (GManager*)_this->m_child;

    lDom->addData(lDom, lCode, "module", lObj->m_module);
    lDom->addData(lDom, lCode, "method", lObj->m_method);
    lDom->addMap(lDom, lCode, _this->m_map);

    lData->assign(lData, lDom->m_dom->toString(lDom->m_dom));
    lDom->delete(lDom);
    return lData;
}
//===============================================
static void GManager_deserialize(GObject* _this, const char* _data) {
    assert(_this);
    const char* lCode = "manager";
    GCode* lDom = GCode_new();
    lDom->m_dom->loadXml(lDom->m_dom, _data);
    GManager* lObj = (GManager*)_this->m_child;

    lObj->m_module = lDom->getData(lDom, lCode, "module");
    lObj->m_method = lDom->getData(lDom, lCode, "method");
    lDom->getMap(lDom, lCode, _this->m_map, _this);

    lDom->delete(lDom);
}
//===============================================
