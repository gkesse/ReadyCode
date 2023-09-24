//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GProcess GProcess;
//===============================================
struct _GProcess {
    void (*delete)(GProcess** _this);
    void (*run)(int _argc, char** _argv);
};
//===============================================
void GProcess_init(GProcess* _this);
GProcess* GProcess_new();
//===============================================
#endif
//===============================================
