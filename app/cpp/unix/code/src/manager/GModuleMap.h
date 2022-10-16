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
    bool onSaveModuleMap();
    bool onSearchModuleMap();
    bool onSearchNextModuleMap();

    bool loadData();
    bool saveModuleMap();
    bool loadPosition();
    bool searchModuleMap();
    bool searchNextModuleMap();
    bool countData();
    bool existeData();
    bool insertData();
    bool updateData();

private:
    int m_id;
    int m_position;
    GModule* m_module;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
