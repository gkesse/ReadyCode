//===============================================
#ifndef _GModuleKey_
#define _GModuleKey_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
class GFormLayout;
//===============================================
class GModuleKey : public GSearch {
public:
    GModuleKey();
    ~GModuleKey();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_key");
    void deserialize(const GString& _data, const GString& _code = "module_key");

    void setModuleKey(const GModuleKey& _moduleKey);
    void setModuleKey(GModuleKey* _moduleKey);
    void setModuleKey(int _index);
    void writeKeyFormModuleNode(GFormLayout* _formLayout);

    void setId(int _id);
    void setModuleId(int _moduleId);
    void setTypeId(int _typeId);
    void setName(const GString& _name);
    void setLabel(const GString& _label);

    int getId() const;
    int getModuleId() const;
    int getTypeId() const;
    GString getName() const;
    GString getLabel() const;
    GString getType() const;
    GString getModule() const;

    void loadModuleKey();
    void saveModuleKey();
    void searchModuleKey();
    void deleteModuleKey();

    bool showList();
    void onNextData();
    bool showNextList();

protected:
    int m_id;
    int m_moduleId;
    int m_typeId;
    GString m_name;
    GString m_label;
    GString m_type;
    GString m_module;
    std::shared_ptr<GTableWidgetUi> m_tableWidget;
};
//==============================================
#endif
//==============================================
