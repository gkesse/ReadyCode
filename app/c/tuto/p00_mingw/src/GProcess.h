//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GProcess GProcess;
//===============================================
struct _GProcess {
    void (*delete)(GProcess** _this);
    void (*inits)(GProcess* _this);
    void (*clean)(GProcess* _this);
    void (*run)(GProcess* _this, int _argc, char** _argv);

    GObject* m_obj;
};
//===============================================
void GProcess_init(GProcess* _this);
GProcess* GProcess_new();
//===============================================
#endif
//===============================================
