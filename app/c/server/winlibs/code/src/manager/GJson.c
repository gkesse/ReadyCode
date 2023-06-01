//===============================================
#include "GJson.h"
#include "GFile.h"
//===============================================
static void GJson_delete(GJson* _this);
static void GJson_clear(GJson* _this);
static void GJson_createObj(GJson* _this);
static void GJson_createArr(GJson* _this);
static void GJson_addObjData(GJson* _this, const char* _key, const char* _value);
static json_object* GJson_addObjObj(GJson* _this, const char* _key);
static json_object* GJson_addObjArr(GJson* _this, const char* _key);
static void GJson_addArrData(GJson* _this, const char* _value);
static json_object* GJson_addArrObj(GJson* _this);
static void GJson_loadFile(GJson* _this, const char* _filename);
static void GJson_loadJson(GJson* _this, const char* _data);
static const char* GJson_toString(GJson* _this);
static void GJson_print(GJson* _this);
//===============================================
GJson* GJson_new() {
    GJson* lObj = (GJson*)malloc(sizeof(GJson));
    lObj->m_logs = GLog_new();
    lObj->m_json = 0;
    lObj->m_isRoot = 0;

    lObj->delete = GJson_delete;
    lObj->clear = GJson_clear;
    lObj->createObj = GJson_createObj;
    lObj->createArr = GJson_createArr;
    lObj->addObjData = GJson_addObjData;
    lObj->addObjObj = GJson_addObjObj;
    lObj->addObjArr = GJson_addObjArr;
    lObj->addArrData = GJson_addArrData;
    lObj->addArrObj = GJson_addArrObj;
    lObj->loadFile = GJson_loadFile;
    lObj->loadJson = GJson_loadJson;
    lObj->toString = GJson_toString;
    lObj->print = GJson_print;
    return lObj;
}
//===============================================
static void GJson_delete(GJson* _this) {
    assert(_this);
    _this->m_logs->delete(_this->m_logs);
    _this->clear(_this);
    free(_this);
}
//===============================================
static void GJson_clear(GJson* _this) {
    assert(_this);
    if(_this->m_isRoot) json_object_put(_this->m_json);
}
//===============================================
static void GJson_createObj(GJson* _this) {
    assert(_this);
    _this->clear(_this);
    _this->m_json = json_object_new_object();
    _this->m_isRoot = 1;
}
//===============================================
static void GJson_createArr(GJson* _this) {
    assert(_this);
    _this->clear(_this);
    _this->m_json = json_object_new_array();
    _this->m_isRoot = 1;
}
//===============================================
static void GJson_addObjData(GJson* _this, const char* _key, const char* _value) {
    assert(_this);
    json_object_object_add(_this->m_json, _key, json_object_new_string(_value));
}
//===============================================
static json_object* GJson_addObjObj(GJson* _this, const char* _key) {
    assert(_this);
    json_object* lObj = json_object_new_object();
    json_object_object_add(_this->m_json, _key, lObj);
    return lObj;
}
//===============================================
static json_object* GJson_addObjArr(GJson* _this, const char* _key) {
    assert(_this);
    json_object* lObj = json_object_new_array();
    json_object_object_add(_this->m_json, _key, lObj);
    return lObj;
}
//===============================================
static void GJson_addArrData(GJson* _this, const char* _value) {
    assert(_this);
    json_object_array_add(_this->m_json, json_object_new_string(_value));
}
//===============================================
static json_object* GJson_addArrObj(GJson* _this) {
    assert(_this);
    json_object* lObj = json_object_new_object();
    json_object_array_add(_this->m_json, lObj);
    return lObj;
}
//===============================================
static void GJson_loadFile(GJson* _this, const char* _filename) {
    assert(_this);
    _this->clear(_this);
    GFile* lFile = GFile_new();
    GString* lData = lFile->load(lFile, _filename);
    _this->m_json = json_tokener_parse(lData->m_data);
    lData->delete(lData);
    lFile->delete(lFile);
}
//===============================================
static void GJson_loadJson(GJson* _this, const char* _data) {
    assert(_this);
    _this->m_json = json_tokener_parse(_data);
}
//===============================================
static const char* GJson_toString(GJson* _this) {
    assert(_this);
    assert(_this->m_json);
    const char* lData = json_object_to_json_string_ext(_this->m_json, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY);
    return lData;
}
//===============================================
static void GJson_print(GJson* _this) {
    assert(_this);
    assert(_this->m_json);
    printf("%s\n", _this->toString(_this));
}
//===============================================
