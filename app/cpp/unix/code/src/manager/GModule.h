//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GSearch.h"
//===============================================
class GModule : public GSearch {
public:
    GModule(const GString& _code = "module");
    ~GModule();
    GObject* clone() const;
    GString serialize(const GString& _code = "module") const;
    bool deserialize(const GString& _data, const GString& _code = "module");

    void setId(int _id);
    int getId() const;

    bool onModule();
    bool onSaveModule();
    bool onSearchModule();
    bool onSearchNextModule();
    bool onDeleteModule();

    bool saveModule();
    bool searchModule();
    bool searchModuleId();
    bool searchModule(const GList& _data);
    bool searchNextModule();
    bool deleteModule();
    bool countSearch();
    bool insertModule();
    bool updateModule();

protected:
    int m_id;
    GString m_name;
};
//==============================================
#endif
//==============================================
