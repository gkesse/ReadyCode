//===============================================
#include "GObject.h"
//===============================================
static void GObject_delete(GObject* _this);
//===============================================
GObject* GObject_new() {
    GObject* lObj = (GObject*)malloc(sizeof(GObject));
    lObj->m_logs = GLog_new();
    lObj->delete = GObject_delete;
    return lObj;
}
//===============================================
static void GObject_delete(GObject* _this) {
    assert(_this);
    _this->m_logs->delete(_this->m_logs);
    free(_this);
}
//===============================================
