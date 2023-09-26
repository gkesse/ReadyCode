//===============================================
#include "GString.h"
#include "GFunctions.h"
//===============================================
static void GString_delete(GString** _this);
static void GString_clear(GString* _this);
static void GString_allocate(GString* _this, int _size);
static void GString_create(GString* _this, const char* _data);
static void GString_assign(GString* _this, GString* _data);
static void GString_add(GString* _this, const char* _data);
static void GString_format(GString* _this, const char* _format, ...);
static void GString_split(GString* _this, GVector* _map, const char* _sep);
static int GString_isEmpty(GString* _this);
static int GString_startsWith(GString* _this, const char* _data);
static int GString_endsWith(GString* _this, const char* _data);
static int GString_indexOf(GString* _this, const char* _data, int _pos);
static void GString_substr(GString* _this, GString* _data, int _pos, int _size);
static void GString_extract(GString* _this, GString* _data, const char* _start, const char* _end);
static void GString_print(GString* _this);
//===============================================
GString* GString_new() {
    GString* lObj = (GString*)malloc(sizeof(GString));
    GString_init(lObj);
    return lObj;
}
//===============================================
void GString_init(GString* _this) {
    assert(_this);
    _this->delete = GString_delete;
    _this->clear = GString_clear;
    _this->allocate = GString_allocate;
    _this->create = GString_create;
    _this->assign = GString_assign;
    _this->add = GString_add;
    _this->format = GString_format;
    _this->split = GString_split;
    _this->isEmpty = GString_isEmpty;
    _this->startsWith = GString_startsWith;
    _this->endsWith = GString_endsWith;
    _this->indexOf = GString_indexOf;
    _this->substr = GString_substr;
    _this->extract = GString_extract;
    _this->print = GString_print;

    _this->m_data = 0;
    _this->m_size = 0;
}
//===============================================
static void GString_delete(GString** _this) {
    assert(*_this);
    (*_this)->clear(*_this);
    free(*_this);
    (*_this) = 0;
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
    assert(_size >= 0);
    _this->clear(_this);
    _this->m_data = (char*)malloc(sizeof(char)*(_size + 1));
    _this->m_data[_size] = '\0';
    _this->m_size = _size;
}
//===============================================
static void GString_create(GString* _this, const char* _data) {
    assert(_this);
    assert(_data);
    int lSize = strlen(_data);
    _this->allocate(_this, lSize);
    memcpy(_this->m_data, _data, _this->m_size);
}
//===============================================
static void GString_assign(GString* _this, GString* _data) {
    assert(_this);
    assert(_data);
    _this->allocate(_this, _data->m_size);
    memcpy(_this->m_data, _data->m_data, _this->m_size);
}
//===============================================
static void GString_add(GString* _this, const char* _data) {
    assert(_this);
    assert(_data);
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
static void GString_format(GString* _this, const char* _format, ...) {
    assert(_this);
    assert(_format);
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lData = (char*)malloc(sizeof(char)*(lSize + 1));
    vsnprintf(lData, lSize + 1, _format, lArgs);
    va_end(lArgs);
    _this->clear(_this);
    _this->m_data = lData;
    _this->m_size = lSize;
}
//===============================================
static void GString_split(GString* _this, GVector* _map, const char* _sep) {
    assert(_this);

    smdelete(_map);
    _map->clear(_map);

    GString* lData = GString_new();
    lData->assign(lData, _this);

    char* lToken = strtok(lData->m_data, _sep);

    while(lToken) {
        GString* lValue = GString_new();
        lValue->create(lValue, lToken);
        _map->add(_map, lValue);
        lToken = strtok(0, _sep);
    }

    lData->delete(&lData);
}
//===============================================
static int GString_isEmpty(GString* _this) {
    assert(_this);
    if(!_this->m_data || !_this->m_size) return 1;
    return 0;
}
//===============================================
static int GString_startsWith(GString* _this, const char* _data) {
    assert(_this);
    if(_this->isEmpty(_this)) return 0;
    int lSize = _this->m_size;
    int lSize2 = strlen(_data);
    if(lSize < lSize2) return 0;
    int lOk = memcmp(_this->m_data, _data, lSize2) == 0;
    return lOk;
}
//===============================================
static int GString_endsWith(GString* _this, const char* _data) {
    assert(_this);
    if(_this->isEmpty(_this)) return 0;
    int lSize = _this->m_size;
    int lSize2 = strlen(_data);
    if(lSize < lSize2) return 0;
    int lPos = lSize - lSize2 - 1;
    int lOk = memcmp(&_this->m_data[lPos], _data, lSize2) == 0;
    return lOk;
}
//===============================================
static int GString_indexOf(GString* _this, const char* _data, int _pos) {
    assert(_this);
    assert(_pos >= 0);
    if(_this->isEmpty(_this)) return -1;
    char* lFound = strstr(&_this->m_data[_pos], _data);
    if(!lFound) return -1;
    int lIndex = lFound - _this->m_data;
    return lIndex;
}
//===============================================
static void GString_substr(GString* _this, GString* _data, int _pos, int _size) {
    assert(_this);
    _data->clear(_data);
    if(_this->isEmpty(_this)) return;
    int lSize = _this->m_size;
    assert(_size >= 0 && _size <= lSize);
    assert(abs(_pos) < lSize);
    if(_pos < 0) {
        if(_size > abs(_pos)) _size = abs(_pos);
        _pos += lSize;
    }
    _data->allocate(_data, _size);
    memcpy(_data->m_data, &_this->m_data[_pos], _size);
}
//===============================================
static void GString_extract(GString* _this, GString* _data, const char* _start, const char* _end) {
    assert(_this);
    _data->clear(_data);
    if(_this->isEmpty(_this)) return;
    int lStart = _this->indexOf(_this, _start, 0);
    if(lStart == -1) return;
    int lPos = lStart + strlen(_start);
    int lEnd = _this->indexOf(_this, _end, lPos);
    if(lEnd == -1) return;
    int lSize = lEnd - lPos;
    _this->substr(_this, _data, lPos, lSize);
}
//===============================================
static void GString_print(GString* _this) {
    assert(_this);
    printf("%s\n", _this->m_data);
}
//===============================================
