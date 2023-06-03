//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GManager GManager;
//===============================================
struct _GManager {
    GObject* m_obj;
    const char* m_module;
    const char* m_method;

    void (*delete)(GManager* _this);
};
//===============================================
GManager* GManager_new();
//===============================================
#endif
//===============================================
