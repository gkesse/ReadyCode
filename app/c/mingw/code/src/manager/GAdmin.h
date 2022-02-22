//===============================================
#ifndef _GAdmin_
#define _GAdmin_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GAdminO GAdminO;
//===============================================
struct _GAdminO {
    void* parent;
    //
    void (*delete)(GAdminO** _obj);
    void (*run)(GAdminO* _obj, int _argc, char** _argv);
    //
    char* m_state;
};
//===============================================
GAdminO* GAdmin_new();
//===============================================
#endif
//===============================================
