//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GTest GTest;
//===============================================
struct _GTest {
    void (*delete)(GTest** _this);
    void (*run)(GTest* _this, int _argc, char** _argv);

    GObject* m_obj;
};
//===============================================
void GTest_init(GTest* _this);
GTest* GTest_new();
//===============================================
#endif
//===============================================
