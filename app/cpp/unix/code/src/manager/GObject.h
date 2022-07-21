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
    virtual void createDoms();
    virtual GObject* clone();
    virtual std::string serialize(bool _isParent, const std::string& _code) const;
    virtual void deserialize(const std::string& _data, const std::string& _code);
    virtual std::string getItem(const std::string& _code, const std::string& _key) const;
    virtual std::string getItem(const std::string& _code, const std::string& _key, int _index) const;
    virtual int countItem(const std::string& _code) const;
    virtual bool clearMap(std::vector<GObject*>& _map);

protected:
    std::shared_ptr<GCode> m_dom;
    std::vector<GObject*> m_map;
};
//===============================================
#endif
//===============================================
