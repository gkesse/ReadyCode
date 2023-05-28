//===============================================
#ifndef _GJson_
#define _GJson_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GJson GJson;
//===============================================
struct _GJson {
    GLog* m_logs;
    struct json_object* m_json;
    GJson* m_next;

    void (*delete)(GJson* _this);
    void (*deleteObj)(GJson* _this);
    void (*clear)(GJson* _this);
    void (*createObj)(GJson* _this);
    void (*createArr)(GJson* _this);
    void (*addObjData)(GJson* _this, const char* _key, const char* _value);
    GJson* (*addObjObj)(GJson* _this, const char* _key);
    GJson* (*addObjArr)(GJson* _this, const char* _key);
    void (*addArrData)(GJson* _this, const char* _value);
    GJson* (*addArrObj)(GJson* _this);
    void (*setNext)(GJson* _this, GJson* _node);
    void (*loadFile)(GJson* _this, const char* _filename);
    void (*loadJson)(GJson* _this, const char* _data);
    const char* (*toString)(GJson* _this);
    void (*print)(GJson* _this);
};
//===============================================
GJson* GJson_new();
//===============================================
#endif
//===============================================