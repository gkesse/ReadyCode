//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
#include "GMap.h"
#include "GCode.h"
#include "GLog.h"
//===============================================
class GObject {
public:
    GObject(const GString& _code = "object");
    virtual ~GObject();
    virtual GObject* clone() const;
    virtual GString serialize(const GString& _code = "object") const;
    virtual bool deserialize(const GString& _data, const GString& _code = "object");
    virtual void clearMap();
    virtual void clearMap(std::vector<GObject*>& _map) const;
    virtual GString getCodeName() const;
    virtual int size() const;
    virtual GObject* at(int _index);
    virtual GObject* back();
    virtual void add(GObject* _obj);
    virtual void print();
    virtual void addError(const GString& _msg);

protected:
    GString m_codeName;
    std::vector<GObject*> m_map;

public:
    GLog m_logs;
};
//===============================================
#endif
//===============================================
