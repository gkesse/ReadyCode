//===============================================
#ifndef _GCode_
#define _GCode_
//===============================================
#include "GXml.h"
//===============================================
typedef struct _GCode GCode;
typedef struct _GVector GVector;
//===============================================
struct _GCode {
    GXml* m_dom;

    void (*delete)(GCode* _this);
    xmlNodePtr (*createDatas)(GCode* _this);
    xmlNodePtr (*createCode)(GCode* _this, const char* _code);
    void (*addData)(GCode* _this, const char* _code, const char* _key, const char* _value);
    const char* (*getData)(GCode* _this, const char* _code, const char* _key);
    void (*addMap)(GCode* _this, const char* _code, GVector* _map);
    void (*addLog)(GCode* _this, const char* _code, GVector* _map);
    void (*getLog)(GCode* _this, const char* _code, GVector* _map, GLog* _obj);
    GString* (*toDatas)(GCode* _this);
};
//===============================================
GCode* GCode_new();
//===============================================
#endif
//===============================================
