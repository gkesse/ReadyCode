//===============================================
#include "GVector.h"
//===============================================
static void GVector_delete(GVector* _this);
static void GVector_add(GVector* _this, void* _data);
static void* GVector_get(GVector* _this, int i);
static int GVector_size(GVector* _this);
static void GVector_clear(GVector* _this);
//===============================================
GVector* GVector_new() {
    GVector* lObj = (GVector*)malloc(sizeof(GVector));
    lObj->m_next = 0;
    lObj->m_data = 0;

    lObj->delete = GVector_delete;
    lObj->add = GVector_add;
    lObj->get = GVector_get;
    lObj->size = GVector_size;
    lObj->clear = GVector_clear;
    return lObj;
}
//===============================================
static void GVector_delete(GVector* _this) {
    assert(_this);
    _this->clear(_this);
    free(_this);
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
