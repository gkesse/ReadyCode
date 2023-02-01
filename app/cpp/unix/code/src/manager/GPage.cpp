//===============================================
#include "GPage.h"
#include "GMySQL.h"
//===============================================
GPage::GPage()
: GSearch() {
    m_id = 0;
    m_parentId = 0;
    m_typeId = 0;
}
//===============================================
GPage::~GPage() {

}
//===============================================
GString GPage::serialize(const GString& _code)  {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "parent_id", m_parentId);
    lDom.addData(_code, "type_id", m_typeId);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "type_name", m_typeName);
    lDom.addData(_code, "title", m_title);
    lDom.addData(_code, "url", m_url);
    lDom.addData(_code, "path", m_path);
    lDom.addData(_code, m_map);
    return lDom.toString();
}
//===============================================
void GPage::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_parentId = lDom.getData(_code, "parent_id").toInt();
    m_typeId = lDom.getData(_code, "type_id").toInt();
    m_name = lDom.getData(_code, "name");
    m_typeName = lDom.getData(_code, "type_name");
    m_title = lDom.getData(_code, "title");
    m_url = lDom.getData(_code, "url");
    m_path = lDom.getData(_code, "path");
    lDom.getData(_code, m_map, this);
}
//===============================================
GObject* GPage::clone() const {
    GPage* lObj = new GPage;
    lObj->setPage(*this);
    return lObj;
}
//===============================================
void GPage::setPage(const GPage& _obj) {
    m_id = _obj.m_id;
    m_parentId = _obj.m_parentId;
    m_typeId = _obj.m_typeId;
    m_name = _obj.m_name;
    m_typeName = _obj.m_typeName;
    m_title = _obj.m_title;
    m_url = _obj.m_url;
    m_path = _obj.m_path;
}
//===============================================
bool GPage::run(const GString& _request) {
    deserialize(_request);
    if(!m_parentId) m_parentId = 1;
    if(m_methodName == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(m_methodName == "save_page") {
        onSavePage();
    }
    else if(m_methodName == "load_page") {
        onLoadPage();
    }
    else if(m_methodName == "search_page") {
        onSearchPage();
    }
    else {
        m_logs.addError("La méthode est inconnu.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onSavePage() {
    if(m_name.isEmpty()) {
        m_logs.addError("Le nom de la page est obligatoire.");
        return false;
    }
    if(!m_typeId) {
        m_logs.addError("Le type de la page est obligatoire.");
        return false;
    }
    if(!isParentDirectory()) {
        m_logs.addError("Le parent de la page est un fichier.");
        return false;
    }
    if(!m_id) {
        insertPage();
    }
    else {
        if(!isTypeNoChange()) {
            m_logs.addError("Le type de la page a changé.");
            return false;
        }
        updatePage();
    }
    if(!m_logs.hasErrors()) {
        m_logs.addLog("La donnée a bien été enregistrée.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onLoadPage() {
    loadPages();
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onSearchPage() {
    if(m_id != 0) {
        m_where += GFORMAT(" and t1._id = %d ", m_id);
    }
    else {
        if(m_parentId != 0) {
            m_where += GFORMAT(" and t1._parent_id = %d ", m_parentId);
        }
        if(!m_name.isEmpty()) {
            m_where += GFORMAT(" and t1._name like '%s%%' ", m_name.c_str());
        }
        if(m_typeId != 0) {
            m_where += GFORMAT(" and t1._type_id = %d ", m_typeId);
        }
    }
    searchPage();
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::insertPage() {
    GMySQL lMySQL;
    lMySQL.execQuery(GFORMAT(""
            " insert into _page "
            " ( _parent_id, _type_id, _name ) "
            " values ( %d, %d, '%s' ) "
            "", m_parentId
            , m_typeId
            , m_name.c_str()
    ));
    m_logs.addLogs(lMySQL.getLogs());
    if(!m_logs.hasErrors()) {
        m_id = lMySQL.getId();
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::updatePage() {
    GMySQL lMySQL;
    lMySQL.execQuery(GFORMAT(""
            " update _page set "
            " _parent_id = %d "
            " , _type_id = %d "
            " , _name = '%s' "
            " where 1 = 1 "
            " and _id = %d "
            "", m_parentId
            , m_typeId
            , m_name.c_str()
            , m_id
    ));
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::loadPages() {
    GMySQL lMySQL;
    GMySQL::GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select t1._id, t1._parent_id, t1._type_id, t1._name, t2._name "
            " from _page t1 "
            " inner join _page_type t2 on 1 = 1 "
            " and t2._id = t1._type_id "
            " where 1 = 1 "
            " and t1._parent_id = %d "
            " order by t1._name asc "
            "", m_parentId
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GMySQL::GRows lDataRow = lDataMap.at(i);
        int j = 0;
        GPage* lObj = new GPage;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_parentId = lDataRow.at(j++).toInt();
        lObj->m_typeId = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_typeName = lDataRow.at(j++);
        m_map.push_back(lObj);
    }
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::searchPage() {
    GMySQL lMySQL;
    GMySQL::GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select t1._id, t1._parent_id, t1._type_id, t1._name, t2._name "
            " from _page t1 "
            " inner join _page_type t2 on 1 = 1 "
            " and t2._id = t1._type_id "
            " %s "
            " order by t2._name, t1._name asc "
            "", m_where.c_str()
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GMySQL::GRows lDataRow = lDataMap.at(i);
        int j = 0;
        GPage* lObj = new GPage;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_parentId = lDataRow.at(j++).toInt();
        lObj->m_typeId = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_typeName = lDataRow.at(j++);
        m_map.push_back(lObj);
    }
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::isParentDirectory() {
    GMySQL lMySQL;
    int lCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _page t1 "
            " where 1 = 1 "
            " and t1._id = %d "
            " and t1._type_id = 2 "
            "", m_parentId
    )).toInt();
    return (lCount);
}
//===============================================
bool GPage::isTypeNoChange() {
    GMySQL lMySQL;
    int lCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _page t1 "
            " where 1 = 1 "
            " and t1._id = %d "
            " and t1._type_id = %d "
            "", m_id
            , m_typeId
    )).toInt();
    return (lCount);
}
//===============================================
