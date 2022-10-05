//===============================================
#ifndef _GModules_
#define _GModules_
//===============================================
#include "GSearch.h"
//===============================================
class GModules : public GSearch {
public:
    GModules();
    ~GModules();
    GObject* clone() const;
    GString serialize(const GString& _code = "modules") const;
    bool deserialize(const GString& _data, const GString& _code = "modules");
    void initModules();

    bool onModule();
    bool onCreateModule();
    bool onSearchModule();
    bool createModule();
    bool searchModule();
    bool countSearch();
    bool insertModule();

protected:
    int m_id;
    GString m_name;
    GString m_where;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
