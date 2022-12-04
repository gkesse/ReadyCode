//===============================================
#ifndef _GModuleKey_
#define _GModuleKey_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
class GModule;
class GModuleType;
//===============================================
class GModuleKey : public GSearch {
public:
    GModuleKey(const GString& _code = "module_key");
    ~GModuleKey();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_key");
    bool deserialize(const GString& _data, const GString& _code = "module_key");

    void setModuleKey(const GModuleKey& _moduleKey);
    void setModuleKey(GModuleKey* _moduleKey);
    void setModuleKey(int _index);
    void setModule(const GModule& _module);
    void setModule(GModule* _module);
    void setModule(const std::shared_ptr<GModule>& _module);
    void setModuleType(const GString& _moduleType);
    GString getModuleType() const;

    void setId(int _id);
    void setName(const GString& _name);
    void setLabel(const GString& _label);

    int getId() const;
    GString getName() const;
    GString getLabel() const;

    void saveModuleKey();
    void searchModuleKey();
    void deleteModuleKey();

    bool showList();
    void onNextData();
    bool showNextList();

protected:
    int m_id;
    GString m_name;
    GString m_label;
    std::shared_ptr<GModule> m_module;
    std::shared_ptr<GModuleType> m_moduleType;
    std::vector<GObject*> m_map;
    std::shared_ptr<GTableWidgetUi> m_tableWidget;
};
//==============================================
#endif
//==============================================
