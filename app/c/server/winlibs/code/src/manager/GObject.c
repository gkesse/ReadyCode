//===============================================
#include "GObject.h"
//===============================================
static void GObject_delete(GObject* _this);
static void GObject_clear(GObject* _this);
static GObject* GObject_clone(GObject* _this);
static GString* GObject_serialize(GObject* _this);
static void GObject_deserialize(GObject* _this, const char* _data);
static void GObject_print(GObject* _this);
//===============================================
GObject* GObject_new() {
    GObject* lObj = (GObject*)malloc(sizeof(GObject));
    lObj->m_logs = GLog_new();
    lObj->m_resp = GCode_new();
    lObj->m_resp->m_dom->createDoc(lObj->m_resp->m_dom);
    lObj->m_resp->createDatas(lObj->m_resp);
    lObj->m_map = GVector_new();
    lObj->m_child = 0;

    lObj->delete = GObject_delete;
    lObj->clear = GObject_clear;
    lObj->clone = GObject_clone;
    lObj->serialize = GObject_serialize;
    lObj->deserialize = GObject_deserialize;
    lObj->print = GObject_print;
    return lObj;
}
//===============================================
static void GObject_delete(GObject* _this) {
    assert(_this);
    _this->clear(_this);
    _this->m_map->delete(_this->m_map);
    free(_this);
}
//===============================================
static void GObject_clear(GObject* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    int lSize = lMap->size(lMap);
    for(int i = 0; i < lSize; i++) {
        GObject* lObj = lMap->get(lMap, i);
        free(lObj);
    }
    lMap->clear(lMap);
}
//===============================================
static void GObject_print(GObject* _this) {
    assert(_this);
    GString* lData = GString_new();
    lData->assign(lData, _this->serialize(_this));
    lData->print(lData);
    lData->delete(lData);
}
//===============================================
static GObject* GObject_clone(GObject* _this) {return GObject_new();}
static GString* GObject_serialize(GObject* _this) {return GString_new();}
static void GObject_deserialize(GObject* _this, const char* _data) {}
//===============================================
