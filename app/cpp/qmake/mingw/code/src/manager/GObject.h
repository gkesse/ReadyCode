//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
class GCode;
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    virtual GObject* clone() const;
    virtual bool createDoms();
    virtual GString serialize() const;
    virtual bool deserialize(const GString& _data);
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
