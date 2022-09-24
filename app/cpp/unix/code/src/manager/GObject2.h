//===============================================
#ifndef _GObject2_
#define _GObject2_
//===============================================
#include "GInclude.h"
#include "GString2.h"
//===============================================
class GCode2;
//===============================================
class GObject2 {
public:
    GObject2();
    virtual ~GObject2();
    virtual GObject2* clone() const;
    virtual bool createDoms();
    virtual GString2 serialize(const GString2& _code) const;
    virtual bool deserialize(const GString2& _data, const GString2& _code);
    virtual void clearMap(std::vector<GObject2*>& _map) const;
    virtual void print() const;

protected:
    std::shared_ptr<GCode2> m_dom;
};
//===============================================
#endif
//===============================================
