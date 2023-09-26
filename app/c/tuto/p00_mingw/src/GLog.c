//===============================================
#include "GLog.h"
//===============================================
static void GLog_delete(GLog** _this);
static void GLog_clear(GLog* _this);
static GLog* GLog_clone(GLog* _this);
static void GLog_setObj(GLog* _this, GLog* _obj);
static void GLog_loadToMap(GLog* _this, int _index);
static void GLog_loadFromMap(GLog* _this, int _index);
static void GLog_addError(GLog* _this, const char* _msg);
static void GLog_addLog(GLog* _this, const char* _msg);
static void GLog_addData(GLog* _this, const char* _msg);
static void GLog_addLogs(GLog* _this, GLog* _obj);
static void GLog_print(GLog* _this);
//===============================================
GLog* GLog_new() {
    GLog* lObj = (GLog*)malloc(sizeof(GLog));
    GLog_init(lObj);
    return lObj;
}
//===============================================
void GLog_init(GLog* _this) {
    assert(_this);
    _this->delete = GLog_delete;
    _this->clear = GLog_clear;
    _this->loadToMap = GLog_loadToMap;
    _this->loadFromMap = GLog_loadFromMap;
    _this->addError = GLog_addError;
    _this->addLog = GLog_addLog;
    _this->addData = GLog_addData;
    _this->addLogs = GLog_addLogs;
    _this->print = GLog_print;

    _this->m_map = GVector_new();
    _this->m_type = 0;
    _this->m_side = 0;
    _this->m_msg = 0;
}
//===============================================
static void GLog_delete(GLog** _this) {
    assert(*_this);
    GVector* lMap = (*_this)->m_map;
    (*_this)->clear(*_this);
    lMap->delete(&lMap);
    free(*_this);
    (*_this) = 0;
}
//===============================================
static void GLog_clear(GLog* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    for(int i = 0; i < lMap->size(lMap); i++) {
        GLog* lObj = lMap->get(lMap, i);
        lObj->delete(&lObj);
    }
    lMap->clear(lMap);
}
//===============================================
static GLog* GLog_clone(GLog* _this) {
    assert(_this);
    GLog* lObj = GLog_new();
    GLog_setObj(lObj, _this);
    return lObj;
}
//===============================================
static void GLog_setObj(GLog* _this, GLog* _obj) {
    assert(_this);
    _this->m_type = _obj->m_type;
    _this->m_side = _obj->m_side;
    _this->m_msg = _obj->m_msg;
}
//===============================================
static void GLog_loadToMap(GLog* _this, int _index) {
    assert(_this);
    assert(_index >= 1);
    GVector* lMap = _this->m_map;
    int lSize = lMap->size(lMap);
    assert(_index <= lSize);
    GLog* lObj = lMap->get(lMap, _index - 1);
    GLog_setObj(lObj, _this);
}
//===============================================
static void GLog_loadFromMap(GLog* _this, int _index) {
    assert(_this);
    assert(_index >= 1);
    GVector* lMap = _this->m_map;
    int lSize = lMap->size(lMap);
    assert(_index <= lSize);
    GLog* lObj = lMap->get(lMap, _index - 1);
    GLog_setObj(_this, lObj);
}
//===============================================
static void GLog_addError(GLog* _this, const char* _msg) {
    assert(_this);
    GVector* lMap = _this->m_map;
    GLog* lObj = GLog_new();
    lObj->m_type = "error";
    lObj->m_side = "server";
    lObj->m_msg = _msg;
    lMap->add(lMap, lObj);
}
//===============================================
static void GLog_addLog(GLog* _this, const char* _msg) {
    assert(_this);
    GVector* lMap = _this->m_map;
    GLog* lObj = GLog_new();
    lObj->m_type = "log";
    lObj->m_side = "server";
    lObj->m_msg = _msg;
    lMap->add(lMap, lObj);
}
//===============================================
static void GLog_addData(GLog* _this, const char* _msg) {
    assert(_this);
    GVector* lMap = _this->m_map;
    GLog* lObj = GLog_new();
    lObj->m_type = "data";
    lObj->m_side = "server";
    lObj->m_msg = _msg;
    lMap->add(lMap, lObj);
}
//===============================================
static void GLog_addLogs(GLog* _this, GLog* _obj) {
    assert(_this);
    GVector* lMap = _this->m_map;
    GVector* lMap2 = _obj->m_map;
    for(int i = 0; i < lMap2->size(lMap2); i++) {
        GLog* lObj = lMap2->get(lMap2, i);
        GLog* lObj2 = GLog_clone(lObj);
        lMap->add(lMap, lObj2);
    }
}
//===============================================
static void GLog_print(GLog* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    for(int i = 0; i < lMap->size(lMap); i++) {
        GLog* lObj = lMap->get(lMap, i);
        printf("[%-6s] : %s\n", lObj->m_type, lObj->m_msg);
    }
}
//===============================================
