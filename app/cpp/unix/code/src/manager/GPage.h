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
    bool onLoadPage();
    bool onLoadPageTree();
    bool onSearchPage();
    bool onDeletePage();
    bool isIndex() const;
    bool insertPage();
    bool clearDefaultPage();
    bool updatePage();
    bool loadPage();
    bool loadPageTree(int _parentId);
    bool loadPageTree(GCode& _dom, int _parentId);
    bool searchPage();
    bool deletePage();
    bool isParentDirectory();
    bool isTypeNoChange();

private:
    int m_id;
    int m_parentId;
    int m_typeId;
    bool m_isDefault;
    GString m_name;
    GString m_typeName;
    GString m_title;
    GString m_url;
    GString m_path;
    GString m_tree;
};
//==============================================
#endif
//==============================================
