//===============================================
#include "GLog.h"
#include "GCode.h"
//===============================================
static void GLog_delete(GLog* _this);
static GLog* GLog_clone(GLog* _this);
static void GLog_setObj(GLog* _this, GLog* _obj);
static GLog* GLog_loadToMap(GLog* _this, int i);
static GLog* GLog_loadFromMap(GLog* _this, int i);
static void GLog_addError(GLog* _this, const char* _msg);
static void GLog_addLog(GLog* _this, const char* _msg);
static void GLog_addData(GLog* _this, const char* _msg);
static void GLog_addLogs(GLog* _this, GLog* _obj);
static void GLog_showErrors(GLog* _this);
static void GLog_showLogs(GLog* _this);
static void GLog_showDatas(GLog* _this);
static void GLog_showLogsA(GLog* _this);
static void GLog_showLogsX(GLog* _this);
static void GLog_clear(GLog* _this);
static int GLog_hasErrors(GLog* _this);
static int GLog_hasLogs(GLog* _this);
static int GLog_hasDatas(GLog* _this);
static GString* GLog_serialize(GLog* _this);
static void GLog_deserialize(GLog* _this, const char* _data);
//===============================================
GLog* GLog_new() {
    GLog* lObj = (GLog*)malloc(sizeof(GLog));

    lObj->m_type = 0;
    lObj->m_msg = 0;
    lObj->m_map = GVector_new();

    lObj->delete = GLog_delete;
    lObj->clone = GLog_clone;
    lObj->setObj = GLog_setObj;
    lObj->loadToMap = GLog_loadToMap;
    lObj->loadFromMap = GLog_loadFromMap;
    lObj->addError = GLog_addError;
    lObj->addLog = GLog_addLog;
    lObj->addData = GLog_addData;
    lObj->addLogs = GLog_addLogs;
    lObj->showErrors = GLog_showErrors;
    lObj->showLogs = GLog_showLogs;
    lObj->showDatas = GLog_showDatas;
    lObj->showLogsA = GLog_showLogsA;
    lObj->showLogsX = GLog_showLogsX;
    lObj->clear = GLog_clear;
    lObj->hasErrors = GLog_hasErrors;
    lObj->hasLogs = GLog_hasLogs;
    lObj->hasDatas = GLog_hasDatas;
    lObj->serialize = GLog_serialize;
    lObj->deserialize = GLog_deserialize;
    return lObj;
}
//===============================================
static void GLog_delete(GLog* _this) {
    assert(_this);
    _this->m_map->delete(_this->m_map);
    free(_this);
}
//===============================================
static GLog* GLog_clone(GLog* _this) {
    assert(_this);
    return GLog_new();
}
//===============================================
static void GLog_setObj(GLog* _this, GLog* _obj) {
    assert(_this);
    _this->m_type = _obj->m_type;
    _this->m_msg = _obj->m_msg;
}
//===============================================
static GLog* GLog_loadToMap(GLog* _this, int i) {
    assert(_this);
    GVector* lMap = _this->m_map;
    if(i <= 0 || i > lMap->size(lMap)) return _this;
    GLog* lObj = lMap->get(lMap, i - 1);
    lObj->setObj(lObj, _this);
    return _this;
}
//===============================================
static GLog* GLog_loadFromMap(GLog* _this, int i) {
    assert(_this);
    GVector* lMap = _this->m_map;
    if(i <= 0 || i > lMap->size(lMap)) return _this;
    GLog* lObj = lMap->get(lMap, i - 1);
    _this->setObj(_this, lObj);
    return _this;
}
//===============================================
static void GLog_addError(GLog* _this, const char* _msg) {
    assert(_this);
    GLog* lObj = GLog_new();
    GVector* lMap = _this->m_map;
    lObj->m_type = "error";
    lObj->m_msg = _msg;
    lMap->add(lMap, lObj);
}
//===============================================
static void GLog_addLog(GLog* _this, const char* _msg) {
    assert(_this);
    GLog* lObj = GLog_new();
    GVector* lMap = _this->m_map;
    lObj->m_type = "log";
    lObj->m_msg = _msg;
    lMap->add(lMap, lObj);
}
//===============================================
static void GLog_addData(GLog* _this, const char* _msg) {
    assert(_this);
    GLog* lObj = GLog_new();
    GVector* lMap = _this->m_map;
    lObj->m_type = "data";
    lObj->m_msg = _msg;
    lMap->add(lMap, lObj);
}
//===============================================
static void GLog_addLogs(GLog* _this, GLog* _obj) {
    assert(_this);
    GVector* lMap = _this->m_map;
    GVector* lVec = _obj->m_map;
    for(int i = 0; i < lVec->size(lVec); i++) {
        GLog* lObj = lVec->get(lVec, i);
        GLog* lNew = GLog_new();
        lNew->setObj(lNew, lObj);
        lMap->add(lMap, lNew);
    }
}
//===============================================
static void GLog_showErrors(GLog* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    for(int i = 0; i < lMap->size(lMap); i++) {
        GLog* lObj = lMap->get(lMap, i);
        if(strcmp(lObj->m_type, "error")) continue;
        printf("[%-5s] : %s\n", lObj->m_type, lObj->m_msg);
    }
}
//===============================================
static void GLog_showLogs(GLog* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    for(int i = 0; i < lMap->size(lMap); i++) {
        GLog* lObj = lMap->get(lMap, i);
        if(strcmp(lObj->m_type, "log")) continue;
        printf("[%-5s] : %s\n", lObj->m_type, lObj->m_msg);
    }
}
//===============================================
static void GLog_showDatas(GLog* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    for(int i = 0; i < lMap->size(lMap); i++) {
        GLog* lObj = lMap->get(lMap, i);
        if(strcmp(lObj->m_type, "data")) continue;
        printf("[%-5s] : %s\n", lObj->m_type, lObj->m_msg);
    }
}
//===============================================
static void GLog_showLogsA(GLog* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    for(int i = 0; i < lMap->size(lMap); i++) {
        GLog* lObj = lMap->get(lMap, i);
        printf("[%-5s] : %s\n", lObj->m_type, lObj->m_msg);
    }
}
//===============================================
static void GLog_showLogsX(GLog* _this) {
    assert(_this);
    GLog* lLog = _this;
    if(lLog->hasDatas(lLog)) {
        lLog->showDatas(lLog);
    }
    else if(lLog->hasLogs(lLog)) {
        lLog->showLogs(lLog);
    }
    else if(lLog->hasDatas(lLog)) {
        lLog->showDatas(lLog);
    }
}
//===============================================
static void GLog_clear(GLog* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    lMap->clear(lMap);
}
//===============================================
static int GLog_hasErrors(GLog* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    for(int i = 0; i < lMap->size(lMap); i++) {
        GLog* lObj = lMap->get(lMap, i);
        if(!strcmp(lObj->m_type, "error")) return 1;
    }
    return 0;
}
//===============================================
static int GLog_hasLogs(GLog* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    for(int i = 0; i < lMap->size(lMap); i++) {
        GLog* lObj = lMap->get(lMap, i);
        if(!strcmp(lObj->m_type, "log")) return 1;
    }
    return 0;
}
//===============================================
static int GLog_hasDatas(GLog* _this) {
    assert(_this);
    GVector* lMap = _this->m_map;
    for(int i = 0; i < lMap->size(lMap); i++) {
        GLog* lObj = lMap->get(lMap, i);
        if(!strcmp(lObj->m_type, "data")) return 1;
    }
    return 0;
}
//===============================================
static GString* GLog_serialize(GLog* _this) {
    assert(_this);
    const char* lCode = "logs";
    GCode* lDom = GCode_new();
    GString* lData = GString_new();
    lDom->m_dom->createDoc(lDom->m_dom);

    lDom->addData(lDom, lCode, "type", _this->m_type);
    lDom->addData(lDom, lCode, "msg", _this->m_msg);
    lDom->addLog(lDom, lCode, _this->m_map);

    lData->assign(lData, lDom->m_dom->toString(lDom->m_dom));
    lDom->delete(lDom);
    return lData;
}
//===============================================
static void GLog_deserialize(GLog* _this, const char* _data) {
    assert(_this);
    const char* lCode = "logs";
    GCode* lDom = GCode_new();
    lDom->m_dom->loadXml(lDom->m_dom, _data);

    _this->m_type = lDom->getData(lDom, lCode, "type");
    _this->m_msg = lDom->getData(lDom, lCode, "msg");
    lDom->getLog(lDom, lCode, _this->m_map, _this);

    lDom->delete(lDom);
}
//===============================================