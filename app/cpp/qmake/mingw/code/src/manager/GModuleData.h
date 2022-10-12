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
    GModuleData();
    ~GModuleData();
    GObject* clone() const;
    GString serialize() const;
    bool deserialize(const GString& _data);

    void setModuleData(const GModuleData& _module);
    void setModuleData(GModuleData* _module);
    void setModuleData(int _index);
    void setModule(GModule* _module);
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
    GModule* m_module;
    GString m_name;
    GString m_value;
    std::vector<GObject*> m_map;
    GTableWidgetUi* m_tableWidget;
};
//==============================================
#endif
//==============================================
