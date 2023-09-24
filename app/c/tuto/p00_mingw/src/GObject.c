//===============================================
#include "GObject.h"
#include "GLog.h"
//===============================================
static void GObject_delete(GObject** _this);
//===============================================
GObject* GObject_new() {
    GObject* lObj = (GObject*)malloc(sizeof(GObject));
    GObject_init(lObj);
    return lObj;
}
//===============================================
void GObject_init(GObject* _this) {
    assert(_this);
    _this->delete = GObject_delete;

    _this->m_logs = GLog_new();
}
//===============================================
static void GObject_delete(GObject** _this) {
    assert(*_this);
    GLog* lLog = (*_this)->m_logs;
    lLog->delete(&lLog);
    free(*_this);
    (*_this) = 0;
}
//===============================================
