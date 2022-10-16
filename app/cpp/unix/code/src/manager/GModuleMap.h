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
    bool onLoadModuleMap();
    bool onAddModuleMap();
    bool onMoveUpModuleMap();
    bool onMoveDownModuleMap();

    bool loadData();
    bool loadPosition();
    bool loadPositionUp();
    bool loadPositionDown();
    bool updatePositionUp();
    bool updatePositionDown();
    bool insertData();

private:
    int m_id;
    int m_position;
    int m_positionUp;
    int m_positionDown;
    GModule* m_module;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
