//===============================================
#ifndef _GModuleNode_
#define _GModuleNode_
//===============================================
#include "GSearch.h"
//===============================================
class GModule;
//===============================================
class GModuleNode : public GSearch {
public:
    GModuleNode(const GString& _code = "module_node");
    ~GModuleNode();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_node") const;
    bool deserialize(const GString& _data, const GString& _code = "module_node");

    bool onModule();
    bool onSaveModuleMap();
    bool onSearchModuleMap();
    bool onNextModuleMap();
    bool onAddModuleMap();
    bool onMoveUpModuleMap();
    bool onMoveDownModuleMap();

    bool checkData();
    bool saveModuleMap();
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
    bool insertData(GModuleNode* _obj);

private:
    int m_id;
    int m_moduleId;
    int m_keyId;
    int m_position;
    int m_positionUp;
    int m_positionDown;
    GString m_value;
};
//==============================================
#endif
//==============================================
