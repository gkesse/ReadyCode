//===============================================
#ifndef _GModuleType_
#define _GModuleType_
//===============================================
#include "GSearch.h"
//===============================================
class GModuleType : public GSearch {
public:
    GModuleType(const GString& _code = "module_type");
    ~GModuleType();
    GObject* clone() const;
    GString serialize(const GString& _code = "module_type") const;
    bool deserialize(const GString& _data, const GString& _code = "module_type");

    int getId() const;

    bool onModule();
    bool onLoadModuleType();
    bool onSaveModuleType();
    bool onSearchModuleType();
    bool onSearchNextModuleType();
    bool onDeleteModuleType();

    bool loadModuleType();
    bool saveModuleType();
    bool searchModuleType();
    bool searchNextModuleType();
    bool deleteModuleType();
    bool countSearch();
    bool insertModuleType();
    bool updateModuleType();

protected:
    int m_id;
    GString m_name;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
