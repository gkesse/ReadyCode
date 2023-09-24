//===============================================
#include "GVector.h"
//===============================================
static void GVector_delete(GVector** _this);
static void GVector_clear(GVector* _this);
static void GVector_add(GVector* _this, void* _data);
static int GVector_size(GVector* _this);
static void* GVector_get(GVector* _this, int i);
//===============================================
GVector* GVector_new() {
    GVector* lObj = (GVector*)malloc(sizeof(GVector));
    GVector_init(lObj);
    return lObj;
}
//===============================================
void GVector_init(GVector* _this) {
    assert(_this);
    _this->delete = GVector_delete;
    _this->clear = GVector_clear;
    _this->add = GVector_add;
    _this->size = GVector_size;
    _this->get = GVector_get;

    _this->m_next = 0;
    _this->m_data = 0;
}
//===============================================
static void GVector_delete(GVector** _this) {
    assert(*_this);
    (*_this)->clear(*_this);
    free(*_this);
    (*_this) = 0;
}
//===============================================
static void GVector_clear(GVector* _this) {
    assert(_this);
    GVector* lNode = _this->m_next;
    while(lNode) {
        GVector* lPrevious = lNode;
        lNode = lNode->m_next;
        free(lPrevious);
    }
    _this->m_next = 0;
}
//===============================================
static void GVector_add(GVector* _this, void* _data) {
    assert(_this);
    GVector* lNode = _this;
    while(lNode->m_next) lNode = lNode->m_next;
    GVector* lObj = GVector_new();
    lObj->m_data = _data;
    lNode->m_next = lObj;
}
//===============================================
static int GVector_size(GVector* _this) {
    assert(_this);
    int lCount = 0;
    GVector* lNode = _this;
    while(lNode->m_next) {
        lCount++;
        lNode = lNode->m_next;
    }
    return lCount;
}
//===============================================
static void* GVector_get(GVector* _this, int i) {
    assert(_this);
    int lSize = _this->size(_this);
    assert(i >= 0 && i < lSize);
    int lCount = 0;
    GVector* lNode = _this->m_next;
    while(lNode) {
        if(lCount == i) break;
        lNode = lNode->m_next;
        lCount++;
    }
    return lNode->m_data;
}
//===============================================
