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
    GString serialize(const GString& _code = "module_data");
    void deserialize(const GString& _data, const GString& _code = "module_data");

    void setModuleData(const GModuleData& _moduleData);
    void setModuleData(GModuleData* _moduleData);
    void setModuleData(int _index);

    void setId(int _id);
    void setModuleId(int _moduleId);
    void setName(const GString& _name);
    void setValue(const GString& _value);

    int getId() const;
    int getModuleId() const;
    GString getName() const;
    GString getValue() const;

    void saveModuleData();
    void searchModuleData();
    void deleteModuleData();

    bool showList();
    void onNextData();
    bool showNextList();

protected:
    int m_id;
    int m_moduleId;
    GString m_name;
    GString m_value;
    GString m_module;
    std::shared_ptr<GTableWidgetUi> m_tableWidget;
};
//==============================================
#endif
//==============================================
