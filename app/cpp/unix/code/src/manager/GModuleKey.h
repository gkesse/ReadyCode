//===============================================
#ifndef _GModuleKey_
#define _GModuleKey_
//===============================================
#include "GSearch.h"
//===============================================
class GModule;
class GModuleType;
//===============================================
class GModuleKey : public GSearch {
public:
    GModuleKey(const GString& _code = "module_key");
    ~GModuleKey();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_key") const;
    bool deserialize(const GString& _data, const GString& _code = "module_key");

    bool onModule();
    bool onSaveModuleKey();
    bool onSearchModuleKey();
    bool onSearchNextModuleKey();

    bool saveModuleKey();
    bool searchModuleKey();
    bool searchNextModuleKey();
    bool countData();
    bool insertData();
    bool updateData();

protected:
    int m_id;
    GString m_name;
    GString m_label;
    int m_type;
    std::shared_ptr<GModule> m_module;
    std::shared_ptr<GModuleType> m_moduleType;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
