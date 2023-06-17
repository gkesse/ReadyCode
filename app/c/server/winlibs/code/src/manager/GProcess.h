//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GProcess GProcess;
//===============================================
struct _GProcess {
    GObject* m_obj;
    void (*delete)(GProcess* _this);
    void (*init)(GProcess* _this);
    void (*clean)(GProcess* _this);
    void (*run)(GProcess* _this, int _argc, char** _argv);
    void (*runTest)(GProcess* _this, int _argc, char** _argv);
    void (*runServer)(GProcess* _this, int _argc, char** _argv);
};
//===============================================
GProcess* GProcess_new();
//===============================================
#endif
//===============================================
