//===============================================
#ifndef _GObject2_
#define _GObject2_
//===============================================
#include "GInclude.h"
#include "GString2.h"
//===============================================
class GCode;
//===============================================
class GObject2 {
public:
    GObject2();
    virtual ~GObject2();
    virtual GString2 serialize(const GString2& _code = "object") const;
    virtual bool deserialize(const GString2& _data, const GString2& _code = "object");
    virtual void print() const;
};
//===============================================
#endif
//===============================================
