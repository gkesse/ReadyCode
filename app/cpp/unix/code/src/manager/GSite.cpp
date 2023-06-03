//===============================================
#include "GSite.h"
#include "GMySQL.h"
//===============================================
GSite::GSite()
: GSearch() {
    m_id = 0;
}
//===============================================
GSite::~GSite() {

}
//===============================================
GObject* GSite::clone() const {
    GSite* lObj = new GSite;
    lObj->setPage(*this);
    return lObj;
}
//===============================================
void GSite::setPage(const GSite& _obj) {
    m_id = _obj.m_id;
    m_name = _obj.m_name;
    m_title = _obj.m_title;
    m_label = _obj.m_label;
}
//===============================================
bool GSite::insertSite() {
    GMySQL lMySQL;
    lMySQL.execQuery(GFORMAT(""
            " insert into _site "
            " ( _name, _title, _label ) "
            " values ( \"%s\", \"%s\", \"%s\" ) "
            "", m_name.c_str()
            , m_title.c_str()
            , m_label.c_str()
    ));
    m_logs.addLogs(lMySQL.getLogs());
    if(!m_logs.hasErrors()) {
        m_id = lMySQL.getId();
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GSite::updateSite() {
    GMySQL lMySQL;
    lMySQL.execQuery(GFORMAT(""
            " update _site set "
            " _name = \"%s\" "
            " , _title = \"%s\" "
            " , _label = \"%s\" "
            " where 1 = 1 "
            " and _id = %d "
            "", m_name.c_str()
            , m_title.c_str()
            , m_label.c_str()
            , m_id
    ));
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GSite::searchSite() {
    GMySQL lMySQL;
    GMySQL::GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select t1._id "
            " , t1._name "
            " , t1._title "
            " , t1._label "
            " from _site t1 "
            " %s "
            " order by t1._name asc "
            "", m_where.c_str()
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GMySQL::GRows lDataRow = lDataMap.at(i);
        int j = 0;
        GSite* lObj = new GSite;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_title = lDataRow.at(j++);
        lObj->m_label = lDataRow.at(j++);
        m_map.push_back(lObj);
    }
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
GString GSite::serialize(const GString& _code)  {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "title", m_title);
    lDom.addData(_code, "label", m_label);
    lDom.addData(_code, m_map);
    return lDom.toString();
}
//===============================================
void GSite::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    m_title = lDom.getData(_code, "title");
    m_label = lDom.getData(_code, "label");
    lDom.getData(_code, m_map, this);
}
//===============================================
bool GSite::run(const GString& _data) {
    deserialize(_data);
    if(m_methodName == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(m_methodName == "save_site") {
        onSaveSite();
    }
    else if(m_methodName == "search_site") {
        onSearchSite();
    }
    else {
        m_logs.addError("La méthode est inconnu.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GSite::onSaveSite() {
    if(m_name.isEmpty()) {
        m_logs.addError("Le nom du site est obligatoire.");
        return false;
    }
    if(m_title.isEmpty()) {
        m_logs.addError("Le titre du site est obligatoire.");
        return false;
    }
    if(m_label.isEmpty()) {
        m_logs.addError("Le libellé du site est obligatoire.");
        return false;
    }
    if(!m_id) {
        insertSite();
    }
    else {
        updateSite();
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GSite::onSearchSite() {
    if(m_id != 0) {
        m_where += GFORMAT(" and t1._id = %d ", m_id);
    }
    else {
        if(!m_name.isEmpty()) {
            m_where += GFORMAT(" and t1._name like '%s%%' ", m_name.c_str());
        }
        if(!m_title.isEmpty()) {
            m_where += GFORMAT(" and t1._title like '%s%%' ", m_title.c_str());
        }
        if(!m_label.isEmpty()) {
            m_where += GFORMAT(" and t1._label like '%s%%' ", m_label.c_str());
        }
    }
    searchSite();
    return !m_logs.hasErrors();
}
//===============================================
