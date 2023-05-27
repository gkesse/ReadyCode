//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GTest GTest;
//===============================================
struct _GTest {
    GObject* m_parent;
    void (*delete)(GTest* _this);
    void (*run)(GTest* _this, int _argc, char** _argv);
    void (*runVector)(GTest* _this, int _argc, char** _argv);
    void (*runLog)(GTest* _this, int _argc, char** _argv);
    void (*runSocketClient)(GTest* _this, int _argc, char** _argv);
    void (*runString)(GTest* _this, int _argc, char** _argv);
    void (*runXml)(GTest* _this, int _argc, char** _argv);
    void (*runJson)(GTest* _this, int _argc, char** _argv);
    void (*runCode)(GTest* _this, int _argc, char** _argv);
    void (*runModule)(GTest* _this, int _argc, char** _argv);
};
//===============================================
GTest* GTest_new();
//===============================================
#endif
//===============================================
