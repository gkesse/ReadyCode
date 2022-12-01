//===============================================
#ifndef _GModuleData_
#define _GModuleData_
//===============================================
#include "GSearch.h"
//===============================================
class GModule;
//===============================================
class GModuleData : public GSearch {
public:
    GModuleData(const GString& _code = "module_data");
    ~GModuleData();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_data") const;
    bool deserialize(const GString& _data, const GString& _code = "module_data");

    bool onModule();
    bool onSaveModuleData();
    bool onSearchModuleData();
    bool onSearchNextModuleData();

    bool saveModuleData();
    bool searchModuleData();
    bool searchNextModuleData();
    bool countData();
    bool existeData();
    bool insertData();
    bool updateData();

protected:
    int m_id;
    GString m_name;
    GString m_value;
    std::shared_ptr<GModule> m_module;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
