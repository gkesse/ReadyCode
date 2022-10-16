//===============================================
#ifndef _GModuleData_
#define _GModuleData_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
class GModule;
//===============================================
class GModuleData : public GSearch {
public:
    GModuleData(const GString& _code = "module_data");
    ~GModuleData();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_data") const;
    bool deserialize(const GString& _data, const GString& _code = "module_data");

    void setModuleData(const GModuleData& _moduleData);
    void setModuleData(GModuleData* _moduleData);
    void setModuleData(int _index);
    void setModule(GModule* _module);

    void setId(int _id);
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
    GString m_name;
    GString m_value;
    GModule* m_module;
    std::vector<GObject*> m_map;
    GTableWidgetUi* m_tableWidget;
};
//==============================================
#endif
//==============================================
