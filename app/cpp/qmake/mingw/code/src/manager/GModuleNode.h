//===============================================
#ifndef _GModuleNode_
#define _GModuleNode_
//===============================================
#include "GSearch.h"
//===============================================
class GModule;
class GModuleKey;
class GFormLayout;
class GTableWidgetUi;
//===============================================
class GModuleNode : public GSearch {
public:
    GModuleNode(const GString& _code = "module_node");
    ~GModuleNode();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_node");
    bool deserialize(const GString& _data, const GString& _code = "module_node");

    void setModuleNode(const GModuleNode& _moduleNode);
    void setModuleNode(GModuleNode* _moduleNode);
    void setModuleNode(const std::shared_ptr<GModuleNode>& _moduleNode);
    void setModuleNode(int _index);
    void setModule(const GModule& _module);
    void setModule(GModule* _module);
    void setModule(const std::shared_ptr<GModule>& _module);
    void setModuleKey(const std::shared_ptr<GModuleKey>& _moduleKey);
    void writeKeyFormModuleNode(GFormLayout* _formLayout);
    std::shared_ptr<GModuleKey>& getModuleKey();

    void setId(int _id);
    void setModuleId(int _moduleId);
    void setMapId(int _mapId);
    void setKeyId(int _keyId);
    void setValue(const GString& _label);

    int getId() const;
    int getModuleId() const;
    int getMapId() const;
    int getKeyId() const;
    GString getValue() const;

    void loadModuleNode();
    void saveModuleNode();
    void searchModuleNode();
    void deleteModuleNode();

    bool showList();
    void onNextData();
    bool showNextList();

protected:
    int m_id;
    int m_moduleId;
    int m_mapId;
    int m_keyId;
    GString m_value;
    std::shared_ptr<GModule> m_module;
    std::shared_ptr<GModuleKey> m_moduleKey;
    std::shared_ptr<GTableWidgetUi> m_tableWidget;
};
//==============================================
#endif
//==============================================
