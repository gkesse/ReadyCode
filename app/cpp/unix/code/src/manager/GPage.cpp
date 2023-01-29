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
    else if(m_methodName == "load_pages") {
        onLoadPages();
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
    if(!m_id) {
        insertPage();
    }
    else {
        updatePage();
    }
    if(!m_logs.hasErrors()) {
        m_logs.addLog("La donnée a bien été enregistrée.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onLoadPages() {
    loadPages();
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
            " _type_id = %d "
            " , _parent_id = %d "
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
            " select _id, _parent_id, _type_id, _name "
            " from _page "
            " where 1 = 1 "
            " and _parent_id = %d "
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
        m_map.push_back(lObj);
    }
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
