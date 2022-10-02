//===============================================
#ifndef _GModules_
#define _GModules_
//===============================================
#include "GModule2.h"
//===============================================
class GModules : public GModule2 {
public:
    GModules();
    ~GModules();

    GObject2* clone() const;

    GString serialize(const GString& _code = "modules") const;
    bool deserialize(const GString& _data, const GString& _code = "modules");

    void setName(const GString& _name);

    void createModule();

protected:
    int m_id;
    GString m_name;
};
//==============================================
#endif
//==============================================
