//===============================================
#ifndef _GVector_
#define _GVector_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GVector GVector;
//===============================================
struct _GVector {
    void (*delete)(GVector** _this);
    void (*clear)(GVector* _this);
    void (*add)(GVector* _this, void* _data);
    int (*size)(GVector* _this);
    void* (*get)(GVector* _this, int i);

    GVector* m_next;
    void* m_data;
};
//===============================================
void GVector_init(GVector* _this);
GVector* GVector_new();
//===============================================
#endif
//===============================================
