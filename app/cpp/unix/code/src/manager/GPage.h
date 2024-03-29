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

    GObject* clone() const;
    void setPage(const GPage& _obj);
    bool loadParentId();
    bool selectParentId();
    bool insertParentId();

    GString serialize(const GString& _code = "page");
    void deserialize(const GString& _data, const GString& _code = "page");
    bool run(const GString& _request);

    bool onSavePage();
    bool onSavePageFile();
    bool onLoadPage();
    bool onLoadPageTree();
    bool onSearchPage();
    bool onSearchPageFile();
    bool onDeletePage();
    bool isRoot() const;
    bool isFile() const;
    bool isDir() const;
    bool isRootFile() const;
    bool isIndex() const;
    bool preparePath();
    bool prepareIdPath();
    bool updateIdPath();
    bool insertPage();
    bool clearDefaultPage();
    bool updatePage();
    bool loadPage();
    bool loadPageTree(int _parentId);
    bool loadPageTree(GCode& _dom, int _parentId);
    bool searchPage();
    bool existPage();
    bool deletePage();
    bool isParentDirectory();
    bool isTypeNoChange();

private:
    int m_id;
    int m_parentId;
    int m_typeId;
    int m_siteId;
    bool m_isDefault;
    GString m_name;
    GString m_typeName;
    GString m_siteName;
    GString m_path;
    GString m_idPath;
    GString m_tree;
    GString m_content;
};
//==============================================
#endif
//==============================================
