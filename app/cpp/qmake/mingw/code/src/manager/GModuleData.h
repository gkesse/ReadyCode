//===============================================
#ifndef _GModuleData_
#define _GModuleData_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
//===============================================
class GModuleData : public GSearch {
public:
    GModuleData();
    ~GModuleData();
    GObject* clone() const;
    GString serialize(const GString& _code = "modules_data") const;
    bool deserialize(const GString& _data, const GString& _code = "modules_data");

    void setModulesData(const GModuleData& _modules);
    void setModulesData(GModuleData* _modules);
    void setModulesData(int _index);
    void setModulesId(int _modulesId);
    void setName(const GString& _name);
    int getId() const;
    GString getName() const;

    void saveModulesData();
    void searchModulesData();
    void deleteModulesData();
    void onNextData();
    bool showList();
    bool showNextList();

protected:
    int m_id;
    int m_modulesId;
    GString m_name;
    GString m_value;
    std::vector<GObject*> m_map;
    GTableWidgetUi* m_tableWidget;
};
//==============================================
#endif
//==============================================
