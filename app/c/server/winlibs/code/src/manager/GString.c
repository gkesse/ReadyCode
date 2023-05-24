//===============================================
#include "GString.h"
//===============================================
static void GString_delete(GString* _this);
static void GString_clear(GString* _this);
static void GString_allocate(GString* _this, int _size);
static void GString_create(GString* _this, const char* _data);
static void GString_clone(GString* _this, GString* _data);
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
    lObj->clone = GString_clone;
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
    _this->m_data = (char*)malloc(sizeof(char)*(_size + 1));
    _this->m_data[_size] = '\0';
    _this->m_size = _size;
}
//===============================================
static void GString_create(GString* _this, const char* _data) {
    assert(_this);
    int lSize = strlen(_data);
    _this->allocate(_this, lSize);
    memcpy(_this->m_data, _data, _this->m_size);
}
//===============================================
static void GString_clone(GString* _this, GString* _data) {
    assert(_this);
    _this->allocate(_this, _data->m_size);
    memcpy(_this->m_data, _data->m_data, _this->m_size);
}
//===============================================
static void GString_print(GString* _this) {
    assert(_this);
    printf("%s\n", _this->m_data);
}
//===============================================
