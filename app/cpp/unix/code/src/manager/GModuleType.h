//===============================================
#ifndef _GModuleType_
#define _GModuleType_
//===============================================
#include "GSearch.h"
//===============================================
class GModuleType : public GSearch {
public:
    GModuleType();
    ~GModuleType();
    GString serialize(const GString& _code = "module_type");
    void deserialize(const GString& _data, const GString& _code = "module_type");
    GObject* clone() const;

    void setId(int _id);

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
    bool searchType();
    bool searchNextModuleType();
    bool deleteModuleType();
    bool countSearch();
    bool insertModuleType();
    bool updateModuleType();

protected:
    int m_id;
    GString m_name;
};
//==============================================
#endif
//==============================================
