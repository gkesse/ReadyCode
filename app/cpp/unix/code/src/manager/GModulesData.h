//===============================================
#ifndef _GModulesData_
#define _GModulesData_
//===============================================
#include "GSearch.h"
//===============================================
class GModulesData : public GSearch {
public:
    GModulesData();
    ~GModulesData();
    GObject* clone() const;
    GString serialize(const GString& _code = "modules") const;
    bool deserialize(const GString& _data, const GString& _code = "modules");
    void initModules();

    bool onModule();
    bool onSaveModulesData();
    bool onSearchModulesData();
    bool onSearchNextModulesData();
    bool saveModulesData();
    bool searchModulesData();
    bool searchNextModuleData();
    bool countModuleData();
    bool insertModulesData();
    bool updateModulesData();

protected:
    int m_id;
    int m_modulesId;
    GString m_name;
    GString m_value;
    GString m_where;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
