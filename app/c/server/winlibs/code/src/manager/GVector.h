//===============================================
#ifndef _GVector_
#define _GVector_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GVector GVector;
//===============================================
struct _GVector {
    GVector* m_next;
    void* m_data;
    const char* m_type;

    void (*delete)(GVector* _this);
    void (*clean)(GVector* _this);
    void (*clear)(GVector* _this);
    void (*add)(GVector* _this, void* _data);
    void (*setObj)(GVector* _this, GVector* _obj);
    void* (*get)(GVector* _this, int i);
    int (*size)(GVector* _this);
    void (*print)(GVector* _this);
};
//===============================================
GVector* GVector_new();
//===============================================
#endif
//===============================================
