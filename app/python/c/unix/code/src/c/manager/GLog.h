//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GVector.h"
#include "GString.h"
//===============================================
typedef struct _GLog GLog;
//===============================================
struct _GLog {
    GString* m_type;
    GString* m_side;
    GString* m_msg;
    GVector* m_map;

    void (*delete)(GLog* _this);
    void (*clear)(GLog* _this);
    GLog* (*clone)(GLog* _this);
    void (*setObj)(GLog* _this, GLog* _obj);
    GLog* (*loadToMap)(GLog* _this, int i);
    GLog* (*loadFromMap)(GLog* _this, int i);
    void (*addError)(GLog* _this, const char* _msg);
    void (*addLog)(GLog* _this, const char* _msg);
    void (*addData)(GLog* _this, const char* _msg);
    void (*addLogs)(GLog* _this, GLog* _obj);
    void (*showErrors)(GLog* _this);
    void (*showLogs)(GLog* _this);
    void (*showDatas)(GLog* _this);
    void (*showLogsA)(GLog* _this);
    void (*showLogsX)(GLog* _this);
    int (*hasErrors)(GLog* _this);
    int (*hasLogs)(GLog* _this);
    int (*hasDatas)(GLog* _this);
    GString* (*serialize)(GLog* _this);
    void (*deserialize)(GLog* _this, const char* _code);
    void (*print)(GLog* _this);
};
//===============================================
GLog* GLog_new();
//===============================================
#endif
//===============================================
