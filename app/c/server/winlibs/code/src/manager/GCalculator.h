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
    const char* m_expression;
    const char* m_result;

    void (*delete)(GCalculator* _this);
    void (*run)(GCalculator* _this, const char* _data);
    void (*onRunCalculator)(GCalculator* _this, const char* _data);
};
//===============================================
GCalculator* GCalculator_new();
//===============================================
#endif
//===============================================
