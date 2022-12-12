//===============================================
#ifndef _GModuleNode_
#define _GModuleNode_
//===============================================
#include "GSearch.h"
//===============================================
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
    void setModuleNode(int _index);
    GModuleNode* getData(int _keyId) const;

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
    GString getKey() const;

    void loadModuleNode();
    void saveModuleNode();
    void searchModuleNode();
    void deleteModuleNode();

protected:
    int m_id;
    int m_moduleId;
    int m_mapId;
    int m_keyId;
    GString m_value;
    GString m_key;
    std::shared_ptr<GTableWidgetUi> m_tableWidget;
};
//==============================================
#endif
//==============================================
