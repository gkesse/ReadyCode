//===============================================
#ifndef _GModuleMap_
#define _GModuleMap_
//===============================================
#include "GSearch.h"
//===============================================
class GModule;
//===============================================
class GModuleMap : public GSearch {
public:
    GModuleMap(const GString& _code = "module_map");
    ~GModuleMap();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_map") const;
    bool deserialize(const GString& _data, const GString& _code = "module_map");

    bool onModule();
    bool onSearchModuleMap();
    bool onLoadModuleMap();
    bool onAddModuleMap();
    bool onMoveUpModuleMap();
    bool onMoveDownModuleMap();

    bool countData();
    bool searchData();
    bool loadData();
    bool loadPositionAppend();
    bool loadPositionUp();
    bool loadPositionDown();
    bool updatePositionUp();
    bool updatePositionDown();
    bool updatePositionBefore();
    bool updatePositionAfter();
    bool insertData();

private:
    int m_id;
    int m_position;
    int m_positionUp;
    int m_positionDown;
    std::shared_ptr<GModule> m_module;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
