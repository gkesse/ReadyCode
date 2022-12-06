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
    bool onLoadModuleKey();
    bool onSaveModuleKey();
    bool onSearchModuleKey();
    bool onSearchNextModuleKey();

    bool loadModuleKey();
    bool saveModuleKey();
    bool searchModuleKey();
    bool searchNextModuleKey();
    bool countData();
    bool insertData();
    bool updateData();

protected:
    int m_id;
    int m_moduleId;
    int m_typeId;
    GString m_name;
    GString m_label;
    std::shared_ptr<GModule> m_module;
    std::shared_ptr<GModuleType> m_moduleType;
};
//==============================================
#endif
//==============================================
