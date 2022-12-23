//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
#include "GMap.h"
#include "GLog.h"
//===============================================
class GCode;
//===============================================
class GObject {
public:
    GObject(const GString& _code = "object");
    virtual ~GObject();
    virtual GObject* clone() const;
    virtual GString serialize(const GString& _code = "object");
    virtual bool deserialize(const GString& _data, const GString& _code = "object");
    virtual void clearMap();
    virtual GString getCodeName() const;
    virtual int size() const;
    virtual GObject* at(int _index) const;
    virtual void add(GObject* _obj);
    virtual void print();

protected:
    std::vector<GObject*> m_map;
    GString m_codeName;
};
//===============================================
#endif
//===============================================
