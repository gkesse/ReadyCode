//===============================================
#ifndef _GHttp_
#define _GHttp_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GHttp GHttp;
//===============================================
struct _GHttp {
    void (*delete)(GHttp** _this);
    void (*toResponse)(GHttp* _this, GString* _data, const char* _msg);
};
//===============================================
void GHttp_init(GHttp* _this);
GHttp* GHttp_new();
//===============================================
#endif
//===============================================
