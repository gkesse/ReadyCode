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

    void setMapId(int _mapId);

    bool insertData();
    bool insertData(GModuleNode* _obj);
    bool updateData();
    bool updateData(GModuleNode* _obj);

private:
    int m_id;
    int m_moduleId;
    int m_mapId;
    int m_keyId;
    GString m_value;
};
//==============================================
#endif
//==============================================
