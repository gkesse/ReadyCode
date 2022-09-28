//===============================================
#ifndef _GObject2_
#define _GObject2_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GCode2;
//===============================================
class GObject2 {
public:
    GObject2();
    virtual ~GObject2();
    virtual GObject2* clone() const;
    virtual bool createDoms();
    virtual GString serialize(const GString& _code = "object") const;
    virtual bool deserialize(const GString& _data, const GString& _code = "object");
    virtual void clearMap(std::vector<GObject2*>& _map) const;
    virtual void print() const;

protected:
    std::shared_ptr<GCode2> m_dom;
};
//===============================================
#endif
//===============================================
