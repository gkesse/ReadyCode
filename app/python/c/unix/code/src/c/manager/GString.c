//===============================================
#include "GString.h"
#include "GVector.h"
#include "GCode.h"
//===============================================
static void GString_delete(GString* _this);
static void GString_clear(GString* _this);
static void GString_allocate(GString* _this, int _size);
static GString* GString_create(GString* _this, const char* _data);
static GString* GString_assign(GString* _this, GString* _data);
static GString* GString_clone(GString* _this, GString* _data);
static void GString_add(GString* _this, const char* _data);
static GVector* GString_split(GString* _this, const char* _data, const char* _sep);
static int GString_isEmpty(GString* _this);
static void GString_print(GString* _this);
//===============================================
GString* GString_new() {
    GString* lObj = (GString*)malloc(sizeof(GString));
    lObj->m_data = 0;
    lObj->m_size = 0;

    lObj->delete = GString_delete;
    lObj->clear = GString_clear;
    lObj->allocate = GString_allocate;
    lObj->create = GString_create;
    lObj->assign = GString_assign;
    lObj->clone = GString_clone;
    lObj->add = GString_add;
    lObj->split = GString_split;
    lObj->isEmpty = GString_isEmpty;
    lObj->print = GString_print;
    return lObj;
}
//===============================================
static void GString_delete(GString* _this) {
    assert(_this);
    _this->clear(_this);
    free(_this);
}
//===============================================
static void GString_clear(GString* _this) {
    assert(_this);
    free(_this->m_data);
    _this->m_data = 0;
    _this->m_size = 0;
}
//===============================================
static void GString_allocate(GString* _this, int _size) {
    assert(_this);
    if(_size < 0) _size = 0;
    _this->clear(_this);
    _this->m_data = (char*)malloc(sizeof(char)*(_size + 1));
    _this->m_data[_size] = '\0';
    _this->m_size = _size;
}
//===============================================
static GString* GString_create(GString* _this, const char* _data) {
    assert(_this);
    int lSize = strlen(_data);
    _this->allocate(_this, lSize);
    memcpy(_this->m_data, _data, _this->m_size);
    return _this;
}
//===============================================
static GString* GString_assign(GString* _this, GString* _data) {
    assert(_this);
    _this->allocate(_this, _data->m_size);
    memcpy(_this->m_data, _data->m_data, _this->m_size);
    _data->delete(_data);
    return _this;
}
//===============================================
static GString* GString_clone(GString* _this, GString* _data) {
    assert(_this);
    _this->allocate(_this, _data->m_size);
    memcpy(_this->m_data, _data->m_data, _this->m_size);
    return _this;
}
//===============================================
static void GString_add(GString* _this, const char* _data) {
    assert(_this);
    int lSize = strlen(_data);
    int lSizeT = _this->m_size + lSize;
    char* lDataT = (char*)malloc(sizeof(char)*(lSizeT + 1));
    memcpy(&lDataT[0], _this->m_data, _this->m_size);
    memcpy(&lDataT[_this->m_size], _data, lSize);
    lDataT[lSizeT] = '\0';
    _this->clear(_this);
    _this->m_data = lDataT;
    _this->m_size = lSizeT;
}
//===============================================
static GVector* GString_split(GString* _this, const char* _data, const char* _sep) {
    assert(_this);
    GVector* lMap = GVector_new();
    GString* lData = GString_new();
    lData->create(lData, _data);

    char* lToken = strtok(lData->m_data, _sep);

    while(lToken) {
        GString* lValue = GString_new();
        lValue->create(lValue, lToken);
        lMap->add(lMap, lValue);
        lToken = strtok(0, _sep);
    }

    lData->delete(lData);
    return lMap;
}
//===============================================
static int GString_isEmpty(GString* _this) {
    assert(_this);
    if(!_this->m_data || !_this->m_size) return 1;
    return 0;
}
//===============================================
static void GString_print(GString* _this) {
    assert(_this);
    printf("%s\n", _this->m_data);
}
//===============================================
