//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GVector.h"
//===============================================
typedef struct _GLog GLog;
//===============================================
struct _GLog {
    const char* m_type;
    const char* m_msg;
    GVector* m_map;

    void (*delete)(GLog* _this);
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
    void (*clear)(GLog* _this);
    int (*hasErrors)(GLog* _this);
    int (*hasLogs)(GLog* _this);
    int (*hasDatas)(GLog* _this);
    const char* (*serialize)(GLog* _this);
    void (*deserialize)(GLog* _this, const char* _code);
};
//===============================================
GLog* GLog_new();
//===============================================
#endif
//===============================================
