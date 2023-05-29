//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GLog.h"
#include "GString.h"
#include "GVector.h"
//===============================================
typedef struct _GObject GObject;
//===============================================
struct _GObject {
    GLog* m_logs;
    GVector* m_map;
    void* m_child;

    void (*delete)(GObject* _this);
    void (*clear)(GObject* _this);
    GObject* (*clone)(GObject* _this);
    GString* (*serialize)(GObject* _this);
    void (*deserialize)(GObject* _this, const char* _data);
    void (*print)(GObject* _this);
};
//===============================================
GObject* GObject_new();
//===============================================
#endif
//===============================================
