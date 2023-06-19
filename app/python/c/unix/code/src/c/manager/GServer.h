//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GServer GServer;
typedef struct _GCode GCode;
//===============================================
struct _GServer {
    GObject* m_obj;

    void (*delete)(GServer* _this);
    GString* (*toString)(GServer* _this);
    void (*run)(GServer* _this, const char* _module, const char* _method, const char* _data);
    void (*runCalculator)(GServer* _this, const char* _module, const char* _method, const char* _data);
};
//===============================================
GServer* GServer_new();
//===============================================
#endif
//===============================================
