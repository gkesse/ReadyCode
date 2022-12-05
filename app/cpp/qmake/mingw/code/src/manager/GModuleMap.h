//===============================================
#ifndef _GModuleMap_
#define _GModuleMap_
//===============================================
#include "GSearch.h"
//===============================================
class GModule;
class GModuleKey;
class GTreeWidgetUi;
class GFormLayout;
//===============================================
class GModuleMap : public GSearch {
public:
    GModuleMap(const GString& _code = "module_map");
    ~GModuleMap();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_map");
    bool deserialize(const GString& _data, const GString& _code = "module_map");

    void setModuleMap(const GModuleMap& _moduleMap);
    void setModuleMap(GModuleMap* _moduleMap);
    void setModuleMap(const std::shared_ptr<GModuleMap>& _moduleMap);
    void setModuleMap(GFormLayout* _formLayout);
    void setModuleMap(int _index);
    void setModule(GModule* _module);
    void setModule(const std::shared_ptr<GModule>& _module);
    void setModuleKey(const std::shared_ptr<GModuleKey>& _moduleKey);

    void setId(int _id);
    void setModuleId(int _moduleId);
    void setKeyId(int _moduleId);
    void setPosition(int _position);

    int getId() const;
    int getModuleId() const;
    int getKeyId() const;
    int getPosition() const;

    void saveModuleMap();
    void searchModuleMap();
    void nextModuleMap();
    void addModuleMap();
    void moveUpModuleMap();
    void moveDownModuleMap();

    bool showList();
    bool showList(std::shared_ptr<GTreeWidgetUi>& _treeWidgetUi);
    void onNextData();
    void onAddData();
    void onMoveUpData();
    void onMoveDownData();

protected:
    int m_id;
    int m_moduleId;
    int m_keyId;
    int m_position;
    GString m_value;
    std::shared_ptr<GModule> m_module;
    std::shared_ptr<GModuleKey> m_moduleKey;
    std::shared_ptr<GTreeWidgetUi> m_treeWidgetUi;
};
//==============================================
#endif
//==============================================
