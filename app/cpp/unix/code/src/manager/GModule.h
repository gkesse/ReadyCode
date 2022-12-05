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

    int getId() const;

    bool onModule();
    bool onSaveModule();
    bool onSearchModule();
    bool onSearchNextModule();

    bool saveModule();
    bool searchModule();
    bool searchNextModule();
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
