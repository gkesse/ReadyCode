//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
class GCode;
class GError;
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    virtual void createDoms();
    virtual GObject* clone();
    virtual std::string serialize(bool _isParent, const std::string& _code);
    virtual void deserialize(const std::string& _data, const std::string& _code);
    virtual std::string getItem(const std::string& _code, const std::string& _data) const;
    virtual std::string getItem(const std::string& _code, const std::string& _key, int _index);
    virtual int countItem(const std::string& _code, const std::string& _key);
    std::shared_ptr<GError>& getErrors();
    bool clearMap(std::vector<GObject*>& _map);

protected:
    std::shared_ptr<GXml> m_dom;
    std::shared_ptr<GError> m_errors;
    std::vector<GObject*> m_map;
};
//===============================================
#endif
//===============================================
