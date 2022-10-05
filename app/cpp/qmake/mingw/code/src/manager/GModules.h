//===============================================
#ifndef _GModules_
#define _GModules_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
//===============================================
class GModules : public GSearch {
public:
    GModules();
    ~GModules();
    GObject* clone() const;
    GString serialize(const GString& _code = "modules") const;
    bool deserialize(const GString& _data, const GString& _code = "modules");

    void setModules(const GModules& _modules);
    void setModules(GModules* _modules);
    void setName(const GString& _name);
    GString getName() const;

    void createModule();
    void searchModule();
    void deleteModule();
    bool showList();
    void onNextData();

protected:
    int m_id;
    GString m_name;
    std::vector<GObject*> m_map;
    GTableWidgetUi* m_tableWidget;
};
//==============================================
#endif
//==============================================
