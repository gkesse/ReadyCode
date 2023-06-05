//===============================================
#ifndef _GCode_
#define _GCode_
//===============================================
#include "GXml.h"
//===============================================
class GCode : public GXml {
public:
    GCode();
    ~GCode();
    xmlNodePtr createDatas();
    xmlNodePtr createCode(const GString& _code);
    void addData(const GString& _code, const GString& _name, const GString& _value);
};
//===============================================
#endif
//===============================================
