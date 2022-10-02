//===============================================
#ifndef _GModules_
#define _GModules_
//===============================================
#include "GModule.h"
//===============================================
class GModules : public GModule {
public:
    GModules();
    ~GModules();

    GObject* clone() const;

    GString serialize(const GString& _code = "module") const;
    bool deserialize(const GString& _data, const GString& _code = "module");

    void assign(const GModules& _modules);

    void setName(const GString& _name);
    GString getName() const;

    void createModule();
    void searchModule();
    void deleteModule();

protected:
    int m_id;
    GString m_name;
};
//==============================================
#endif
//==============================================
