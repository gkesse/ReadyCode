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
    virtual void clearMap();
    const GLog& getLogs() const;
    const GLog& getDataLogs() const;
    virtual GString serialize(const GString& _code = "object") const;
    virtual void deserialize(const GString& _data, const GString& _code = "object");

protected:
    GLog m_logs;
    GLog m_dataLogs;
    GCode m_resp;
    std::vector<GObject*> m_map;
};
//===============================================
#endif
//===============================================
