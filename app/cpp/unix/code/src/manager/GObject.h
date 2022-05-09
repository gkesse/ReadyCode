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
    virtual std::string getItem(const std::string& _code, const std::string& _data) const;
    virtual std::string getItem(const std::string& _code, const std::string& _key, int _index);
    virtual int countItem(const std::string& _code, const std::string& _key);
    std::shared_ptr<GError>& getErrors();

protected:
    std::shared_ptr<GXml> m_dom;
    std::shared_ptr<GError> m_errors;
};
//===============================================
#endif
//===============================================
