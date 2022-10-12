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
    GString serialize(const GString& _code = "module_data") const;
    bool deserialize(const GString& _data, const GString& _code = "module_data");

    void setModuleData(const GModuleData& _module);
    void setModuleData(GModuleData* _module);
    void setModuleData(int _index);
    void setModuleId(int _moduleId);
    void setName(const GString& _name);
    void setValue(const GString& _value);
    int getId() const;
    GString getName() const;
    GString getValue() const;

    void saveModuleData();
    void searchModuleData();
    void deleteModuleData();
    void onNextData();
    bool showList();
    bool showNextList();

protected:
    int m_id;
    int m_moduleId;
    GString m_name;
    GString m_value;
    std::vector<GObject*> m_map;
    GTableWidgetUi* m_tableWidget;
};
//==============================================
#endif
//==============================================
