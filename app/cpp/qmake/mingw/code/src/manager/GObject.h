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
    GObject(const GString& _code = "object");
    virtual ~GObject();
    virtual GObject* clone() const;
    virtual bool createDoms();
    virtual GString serialize(const GString& _code = "object");
    virtual bool deserialize(const GString& _data, const GString& _code = "object");
    virtual void clearMap();
    virtual void clearMap(std::vector<GObject*>& _map) const;
    virtual GString getCodeName() const;
    virtual bool isOnlyObjectCopied() const;
    virtual void setOnlyObjectCopied();
    virtual void resetOnlyObjectCopied();
    virtual int size() const;
    virtual GObject* at(int _index);
    virtual void print();

protected:
    std::shared_ptr<GCode> m_dom;
    std::vector<GObject*> m_map;
    GString m_codeName;
    bool m_isOnlyObjectCopied;
};
//===============================================
#endif
//===============================================
