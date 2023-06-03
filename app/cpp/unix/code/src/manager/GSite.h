//===============================================
#ifndef _GSite_
#define _GSite_
//===============================================
#include "GSearch.h"
//===============================================
class GSite : public GSearch {
public:
    GSite();
    ~GSite();
    GObject* clone() const;
    void setPage(const GSite& _obj);
    bool insertSite();
    bool updateSite();
    bool searchSite();
    GString serialize(const GString& _code = "site");
    void deserialize(const GString& _data, const GString& _code = "site");
    bool run(const GString& _data);
    bool onSaveSite();
    bool onSearchSite();

private:
    int m_id;
    GString m_name;
    GString m_title;
    GString m_label;
};
//==============================================
#endif
//==============================================
