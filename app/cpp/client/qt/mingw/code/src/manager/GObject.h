//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
#include "GString.h"
#include "GLog.h"
#include "GCode.h"
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    virtual GObject* clone() const;
    virtual void setObj(const GObject& _obj);
    virtual void clearMap();
    virtual void loadFromMap(int i);
    virtual void loadToMap(int i);
    virtual const GLog& getLogs() const;
    virtual int size() const;
    virtual GString serialize(const GString& _code = "object") const;
    virtual void deserialize(const GString& _data, const GString& _code = "object");

protected:
    GLog m_logs;
    GCode m_resp;
    std::vector<GObject*> m_map;
};
//===============================================
#endif
//===============================================
