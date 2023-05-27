//===============================================
#include "GVector.h"
#include "GString.h"
//===============================================
static void GVector_delete(GVector* _this);
static void GVector_clean(GVector* _this);
static void GVector_clear(GVector* _this);
static void GVector_add(GVector* _this, void* _data);
static void* GVector_get(GVector* _this, int i);
static int GVector_size(GVector* _this);
static void GVector_print(GVector* _this);
//===============================================
GVector* GVector_new() {
    GVector* lObj = (GVector*)malloc(sizeof(GVector));
    lObj->m_next = 0;
    lObj->m_data = 0;
    lObj->m_type = "gstring";

    lObj->delete = GVector_delete;
    lObj->clean = GVector_clean;
    lObj->clear = GVector_clear;
    lObj->add = GVector_add;
    lObj->get = GVector_get;
    lObj->size = GVector_size;
    lObj->print = GVector_print;
    return lObj;
}
//===============================================
static void GVector_delete(GVector* _this) {
    assert(_this);
    _this->clear(_this);
    free(_this);
}
//===============================================
static void GVector_clean(GVector* _this) {
    assert(_this);
    GVector* lObj = _this->m_next;
    while(1) {
        if(!lObj) break;
        free(lObj->m_data);
        lObj->m_data = 0;
        lObj = lObj->m_next;
    }
}
//===============================================
static void GVector_clear(GVector* _this) {
    assert(_this);
    GVector* lObj = _this->m_next;
    while(1) {
        if(!lObj) break;
        GVector* lPrevious = lObj;
        lObj = lObj->m_next;
        free(lPrevious);
    }
    _this->m_next = 0;
}
//===============================================
static void GVector_add(GVector* _this, void* _data) {
    assert(_this);
    GVector* lObj = _this;
    while(1) {
        if(!lObj->m_next) break;
        lObj = lObj->m_next;
    }
    GVector* lNew = GVector_new();
    lNew->m_data = _data;
    lObj->m_next = lNew;
}
//===============================================
static void* GVector_get(GVector* _this, int i) {
    assert(_this);
    int lSize = _this->size(_this);
    assert(i >= 0 && i < lSize);
    int lCount = 0;
    GVector* lObj = _this->m_next;
    while(1) {
        assert(lObj);
        if(lCount == i) break;
        lObj = lObj->m_next;
        lCount++;
    }
    return lObj->m_data;
}
//===============================================
static int GVector_size(GVector* _this) {
    assert(_this);
    int lSize = 0;
    GVector* lObj = _this->m_next;
    while(1) {
        if(!lObj) break;
        lObj = lObj->m_next;
        lSize++;
    }
    return lSize;
}
//===============================================
static void GVector_print(GVector* _this) {
    assert(_this);
    if(!strcmp(_this->m_type, "gstring")) {
        for(int i = 0; i  < _this->size(_this); i++) {
            GString* lData = _this->get(_this, i);
            lData->print(lData);
        }
    }
}
//===============================================
