//===============================================
#ifndef _GModuleMap_
#define _GModuleMap_
//===============================================
#include "GSearch.h"
//===============================================
class GModuleMap : public GSearch {
public:
    GModuleMap(const GString& _code = "module_map");
    ~GModuleMap();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_map") const;
    bool deserialize(const GString& _data, const GString& _code = "module_map");

    bool onModule();
    bool onSaveModuleMap();
    bool onSearchModuleMap();
    bool onNextModuleMap();
    bool onAddModuleMap();
    bool onMoveUpModuleMap();
    bool onMoveDownModuleMap();

    bool saveModuleMap();
    bool searchModuleMap();
    bool countData();
    bool loadData();
    bool loadPositionAppend();
    bool loadPositionUp();
    bool loadPositionDown();
    bool updatePositionUp();
    bool updatePositionDown();
    bool updatePositionBefore();
    bool updatePositionAfter();
    bool insertData();
    bool insertData(GModuleMap* _obj);
    bool updateData();

private:
    int m_id;
    int m_moduleId;
    int m_position;
    int m_positionUp;
    int m_positionDown;
    GString m_node;
};
//==============================================
#endif
//==============================================
