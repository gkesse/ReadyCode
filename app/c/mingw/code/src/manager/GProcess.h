//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GProcessO GProcessO;
//===============================================
struct _GProcessO {
    void* parent;
    //
    void (*delete)(GProcessO** _obj);
    void (*run)(GProcessO* _obj, int _argc, char** _argv);
};
//===============================================
GProcessO* GProcess_new();
GProcessO* GProcess();
//===============================================
#endif
//===============================================
