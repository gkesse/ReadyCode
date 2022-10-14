//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GCode;
//===============================================
class GObject {
public:
    GObject(const GString& _code = "object");
    virtual ~GObject();
    virtual GObject* clone() const;
    virtual bool createDoms();
    virtual GString serialize(const GString& _code = "object") const;
    virtual bool deserialize(const GString& _data, const GString& _code = "object");
    virtual void clearMap(std::vector<GObject*>& _map) const;
    virtual GString getCodeName() const;
    virtual void print() const;

protected:
    std::shared_ptr<GCode> m_dom;
    GString m_codeName;
};
//===============================================
#endif
//===============================================
