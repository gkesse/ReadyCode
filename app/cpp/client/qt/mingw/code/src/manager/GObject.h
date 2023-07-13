//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
#include "GString.h"
#include "GLog.h"
#include "GCode.h"
//===============================================
#define GOBJECT     GObject::Instance()
#define spath       GOBJECT->getPath
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    static GObject* Instance();
    virtual GObject* clone() const;
    virtual void setObj(const GObject& _obj);
    virtual void clearMap();
    virtual void loadFromMap(int i);
    virtual void loadToMap(int i);
    virtual const GLog& getLogs() const;
    virtual GString getEnv(const GString& _env, const GString& _defaultValue = "") const;
    virtual GString getPath(const GString& _path) const;
    virtual int size() const;
    virtual GString serialize(const GString& _code = "object") const;
    virtual void deserialize(const GString& _data, const GString& _code = "object");

private:
    static GObject* m_instance;

protected:
    GLog m_logs;
    GLog m_dataLogs;
    GCode m_resp;
    std::vector<GObject*> m_map;
};
//===============================================
#endif
//===============================================
