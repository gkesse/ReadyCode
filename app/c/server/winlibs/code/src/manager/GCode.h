//===============================================
#ifndef _GCode_
#define _GCode_
//===============================================
#include "GXml.h"
//===============================================
typedef struct _GCode GCode;
//===============================================
struct _GCode {
    GXml* m_dom;

    void (*delete)(GCode* _this);
    xmlNodePtr (*createDatas)(GCode* _this);
    xmlNodePtr (*createCode)(GCode* _this, const char* _code);
    void (*addData)(GCode* _this, const char* _code, const char* _key, const char* _value);
};
//===============================================
GCode* GCode_new();
//===============================================
#endif
//===============================================
