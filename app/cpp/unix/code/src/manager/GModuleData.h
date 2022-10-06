//===============================================
#ifndef _GModuleData_
#define _GModuleData_
//===============================================
#include "GSearch.h"
//===============================================
class GModuleData : public GSearch {
public:
    GModuleData();
    ~GModuleData();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_data") const;
    bool deserialize(const GString& _data, const GString& _code = "module_data");
    void initModuleData();

    bool onModule();
    bool onSaveModuleData();
    bool onSearchModuleData();
    bool onSearchNextModuleData();
    bool saveModulesData();
    bool searchModulesData();
    bool searchNextModuleData();
    bool countModuleData();
    bool insertModuleData();
    bool updateModuleData();

protected:
    int m_id;
    int m_moduleId;
    GString m_name;
    GString m_value;
    GString m_where;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
