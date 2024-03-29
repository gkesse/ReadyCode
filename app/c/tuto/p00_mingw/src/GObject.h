//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GLog.h"
#include "GString.h"
//===============================================
typedef struct _GObject GObject;
//===============================================
struct _GObject {
    void (*delete)(GObject** _this);

    GLog* m_logs;
};
//===============================================
void GObject_init(GObject* _this);
GObject* GObject_new();
//===============================================
#endif
//===============================================
