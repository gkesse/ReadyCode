//===============================================
#ifndef _GModuleKey_
#define _GModuleKey_
//===============================================
#include "GSearch.h"
//===============================================
class GModuleKey : public GSearch {
public:
    GModuleKey();
    ~GModuleKey();
    GString serialize(const GString& _code = "module_key");
    void deserialize(const GString& _data, const GString& _code = "module_key");
    GObject* clone() const;

    void setId(int _id);
    void setModuleId(int _moduleId);

    bool onModule();
    bool onLoadModuleKey();
    bool onSaveModuleKey();
    bool onSearchModuleKey();
    bool onSearchNextModuleKey();

    bool loadModuleKey();
    bool saveModuleKey();
    bool searchKey();
    bool searchModuleKey();
    bool searchNextModuleKey();
    bool countData();
    bool insertData();
    bool updateData();

protected:
    int m_id;
    int m_moduleId;
    int m_typeId;
    GString m_name;
    GString m_label;
    GString m_type;
    GString m_module;
};
//==============================================
#endif
//==============================================
