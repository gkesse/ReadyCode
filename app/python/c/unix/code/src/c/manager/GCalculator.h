//===============================================
#ifndef _GCalculator_
#define _GCalculator_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GCalculator GCalculator;
//===============================================
struct _GCalculator {
    GObject* m_obj;
    GString* m_expression;
    GString* m_result;

    void (*delete)(GCalculator* _this);
    void (*run)(GCalculator* _this, const char* _module, const char* _method, const char* _data);
    void (*onRunCalculator)(GCalculator* _this, const char* _module, const char* _method, const char* _data);
};
//===============================================
GCalculator* GCalculator_new();
//===============================================
#endif
//===============================================
