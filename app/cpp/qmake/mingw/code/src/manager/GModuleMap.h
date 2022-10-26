//===============================================
#ifndef _GModuleMap_
#define _GModuleMap_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
class GTreeWidgetUi;
class GModule;
//===============================================
class GModuleMap : public GSearch {
public:
    GModuleMap(const GString& _code = "module_map");
    ~GModuleMap();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_map") const;
    bool deserialize(const GString& _data, const GString& _code = "module_map");

    void setModuleMap(const GModuleMap& _moduleMap);
    void setModuleMap(GModuleMap* _moduleMap);
    void setModuleMap(int _index);
    void setModule(const GModule* _module);
    void setModule(const std::shared_ptr<GModule>& _module);

    void setId(int _id);
    void setPosition(int _position);

    int getId() const;
    int getPosition() const;

    void searchModuleMap();
    void loadModuleMap();
    void addModuleMap();
    void moveUpModuleMap();
    void moveDownModuleMap();

    bool showList();

protected:
    int m_id;
    int m_position;
    GModule* m_module;
    std::vector<GObject*> m_map;
    GTreeWidgetUi* m_treeWidgetUi;
};
//==============================================
#endif
//==============================================
