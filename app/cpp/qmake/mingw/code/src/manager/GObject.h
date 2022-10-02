//===============================================
#ifndef _GObject2_
#define _GObject2_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GCode2;
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    virtual GObject* clone() const;
    virtual bool createDoms();
    virtual GString serialize(const GString& _code = "object") const;
    virtual bool deserialize(const GString& _data, const GString& _code = "object");
    virtual void clearMap(std::vector<GObject*>& _map) const;
    virtual void print() const;

protected:
    std::shared_ptr<GCode2> m_dom;
};
//===============================================
#endif
//===============================================
