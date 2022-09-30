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
    GObject();
    virtual ~GObject();
    virtual void createDoms();
    virtual GObject* clone();
    virtual GString serialize(const GString& _code) const;
    virtual void deserialize(const GString& _data, const GString& _code);
    virtual GString getItem(const GString& _code, const GString& _key) const;
    virtual GString getItem(const GString& _code, const GString& _key, int _index) const;
    virtual int countItem(const GString& _code) const;
    virtual bool clearMap(std::vector<GObject*>& _map);
    virtual void setIsParent(bool _isParent);

protected:
    std::shared_ptr<GCode> m_dom;
    bool m_isParent;
};
//===============================================
#endif
//===============================================
