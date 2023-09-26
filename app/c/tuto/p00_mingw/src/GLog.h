//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GVector.h"
//===============================================
typedef struct _GLog GLog;
//===============================================
struct _GLog {
    void (*delete)(GLog** _this);
    void (*clear)(GLog* _this);
    void (*loadToMap)(GLog* _this, int _index);
    void (*loadFromMap)(GLog* _this, int _index);
    void (*addError)(GLog* _this, const char* _msg);
    void (*addLog)(GLog* _this, const char* _msg);
    void (*addData)(GLog* _this, const char* _msg);
    void (*addLogs)(GLog* _this, GLog* _obj);
    void (*print)(GLog* _this);

    GVector* m_map;
    const char* m_type;
    const char* m_side;
    const char* m_msg;
};
//===============================================
void GLog_init(GLog* _this);
GLog* GLog_new();
//===============================================
#endif
//===============================================
