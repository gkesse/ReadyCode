//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GLogO GLogO;
//===============================================
struct _GLogO {
    void* parent;
    //
    void (*delete)(GLogO* _obj);
    void (*run)(GLogO* _obj, int _argc, char** _argv);
    void (*runTest)(GLogO* _obj, int _argc, char** _argv);
};
//===============================================
GLogO* GLog_new();
//===============================================
#endif
//===============================================
