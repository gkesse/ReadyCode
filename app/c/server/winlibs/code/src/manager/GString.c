//===============================================
#include "GString.h"
#include "GVector.h"
#include "GJson.h"
//===============================================
static void GString_delete(GString* _this);
static void GString_clear(GString* _this);
static void GString_allocate(GString* _this, int _size);
static GString* GString_create(GString* _this, const char* _data);
static GString* GString_assign(GString* _this, GString* _data);
static void GString_add(GString* _this, const char* _data);
static const char* GString_format(GString* _this, const char* _format, ...);
static GVector* GString_split(GString* _this, const char* _data, const char* _sep);
static GString* GString_toBase64(GString* _this);
static GString* GString_toJson(GString* _this);
static GString* GString_fromBase64(GString* _this);
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
    lObj->add = GString_add;
    lObj->format = GString_format;
    lObj->split = GString_split;
    lObj->toBase64 = GString_toBase64;
    lObj->toJson = GString_toJson;
    lObj->fromBase64 = GString_fromBase64;
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
static const char* GString_format(GString* _this, const char* _format, ...) {
    assert(_this);
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lData = (char*)malloc(sizeof(char)*(lSize + 1));
    vsnprintf(lData, lSize + 1, _format, lArgs);
    va_end(lArgs);
    _this->clear(_this);
    _this->m_data = lData;
    _this->m_size = lSize;
    return _this->m_data;
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
static GString* GString_toBase64(GString* _this) {
    assert(_this);
    char* lBuffer = b64_encode(_this->m_data, _this->m_size);
    _this->create(_this, lBuffer);
    free(lBuffer);
    return _this;
}
//===============================================
static GString* GString_toJson(GString* _this) {
    assert(_this);
    //GJson* lJson = GJson_new();
    return _this;
}
//===============================================
static GString* GString_fromBase64(GString* _this) {
    assert(_this);
    char* lBuffer = b64_decode(_this->m_data, _this->m_size);
    _this->create(_this, lBuffer);
    free(lBuffer);
    return _this;
}
//===============================================
static void GString_print(GString* _this) {
    assert(_this);
    printf("%s\n", _this->m_data);
}
//===============================================
