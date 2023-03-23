//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
#include "GMap.h"
#include "GCode.h"
#include "GLog.h"
#include "GLogUi.h"
#include "GLogTrace.h"
#include "GJson.h"
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    virtual GObject* clone() const;
    virtual void setObj(const GObject& _obj);
    virtual GString serialize(const GString& _code = "object");
    virtual void deserialize(const GString& _data, const GString& _code = "object");
    virtual void clearMap();
    virtual void clearMap(std::vector<GObject*>& _map) const;
    virtual int size() const;
    virtual GObject* at(int _index);
    virtual GObject* back();
    virtual void add(GObject* _obj);
    virtual void addToMap(const GObject& _obj);
    virtual void print();
    virtual void showErrors();
    virtual void addLogs(const GLog& _obj);
    virtual const GLog& getLogs() const;
    virtual GString toResponse() const;
    virtual GString toJson();

protected:
    GLog m_logs;
    std::vector<GObject*> m_map;
    GCode m_responseXml;
};
//===============================================
#endif
//===============================================
