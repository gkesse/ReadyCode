//===============================================
#ifndef _GPage_
#define _GPage_
//===============================================
#include "GSearch.h"
//===============================================
class GPage : public GSearch {
public:
    GPage();
    ~GPage();
    GString serialize(const GString& _code = "page");
    void deserialize(const GString& _data, const GString& _code = "page");
    GObject* clone() const;
    void setPage(const GPage& _obj);
    bool run(const GString& _request);
    bool onSavePage();
    bool insertPage();
    bool updatePage();

private:
    int m_id;
    int m_parentId;
    GString m_name;
    GString m_title;
    GString m_url;
    GString m_path;
};
//==============================================
#endif
//==============================================
