//===============================================
#ifndef _GModuleMap_
#define _GModuleMap_
//===============================================
#include "GSearch.h"
//===============================================
class GTreeWidgetUi;
class GModule;
class GFormLayout;
class GModuleKey;
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
    void setModuleMap(int _index);
    void setModule(GModule* _module);
    void setModule(const std::shared_ptr<GModule>& _module);

    void setId(int _id);
    void setModuleMap(const std::shared_ptr<GModuleKey>& _keys, GFormLayout* _formLayout);

    int getId() const;

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
    int m_position;
    GString m_key;
    GString m_value;
    std::shared_ptr<GModule> m_module;
    std::shared_ptr<GTreeWidgetUi> m_treeWidgetUi;
};
//==============================================
#endif
//==============================================
