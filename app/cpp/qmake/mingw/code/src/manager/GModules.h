//===============================================
#ifndef _GModules_
#define _GModules_
//===============================================
#include "GModule.h"
//===============================================
class GTableWidgetUi;
//===============================================
class GModules : public GModule {
public:
    GModules();
    ~GModules();

    GObject* clone() const;

    GString serialize(const GString& _code = "module") const;
    bool deserialize(const GString& _data, const GString& _code = "module");

    void assign(const GModules& _modules);
    void assign(GModules* _modules);

    void setName(const GString& _name);
    GString getName() const;

    void createModule();
    void searchModule();
    void deleteModule();
    bool showList();

protected:
    int m_id;
    GString m_name;
    std::vector<GObject*> m_map;
    GTableWidgetUi* m_tableWidget;
};
//==============================================
#endif
//==============================================
