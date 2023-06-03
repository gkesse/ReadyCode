//===============================================
#ifndef _GCalculator_
#define _GCalculator_
//===============================================
#include "GManager.h"
//===============================================
typedef struct _GCalculator GCalculator;
//===============================================
struct _GCalculator {
    GManager* m_mgr;
    GObject* m_obj;
    GString* m_expression;
    GString* m_result;

    void (*delete)(GCalculator* _this);
    void (*run)(GCalculator* _this, const char* _data);
    void (*onRunCalculator)(GCalculator* _this, const char* _data);
};
//===============================================
GCalculator* GCalculator_new();
//===============================================
#endif
//===============================================
