//===============================================
#include "GQueryType.h"
#include "GMySQL.h"
#include "GSocket.h"
#include "GCode.h"
//===============================================
GQueryType::GQueryType()
: GSearch() {
    m_id = 0;
}
//===============================================
GQueryType::~GQueryType() {
    clearMap();
}
//===============================================
GObject* GQueryType::clone() const {
    return new GQueryType;
}
//===============================================
GString GQueryType::serialize(const GString& _code)  {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, m_map);
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
void GQueryType::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    lDom.getData(_code, m_map, this);
}
//===============================================
void GQueryType::setId(int _id) {
    m_id = _id;
}
//===============================================
int GQueryType::getId() const {
    return m_id;
}
//===============================================
bool GQueryType::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        m_logs.addError("Erreur la méthode est obligatoire.");
    }
    else if(m_methodName == "save_query_type") {
        onSaveQueryType();
    }
    else if(m_methodName == "search_query_type") {
        onSearchQueryType();
    }
    else if(m_methodName == "search_next_query_type") {
        onSearchNextQueryType();
    }
    else if(m_methodName == "delete_query_type") {
        onDeleteQueryType();
    }
    else {
        m_logs.addError("Erreur la méthode est inconnue.");
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GQueryType::onSaveQueryType() {
    if(m_name == "") {GERROR_ADD(eGERR, "Le nom de la donnée est obligatoire."); return false;}
    if(!saveData()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de l'enregistrement de la donnée."); return false;}
    m_logs.addLog("La donnée a bien été enregistrée.");
    return true;
}
//===============================================
bool GQueryType::onSearchQueryType() {
    if(m_id != 0) {
        m_where += GFORMAT(" and _id = %d ", m_id);
    }
    else {
        if(m_name != "") {
            m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
        }
    }
    if(!countSearch()) return false;
    if(!searchData()) return false;
    if(size() == 0) {GERROR_ADD(eGERR, "Aucun résultat n'a été trouvé."); return false;}
    return true;
}
//===============================================
bool GQueryType::onSearchNextQueryType() {
    if(!m_hasData) {GERROR_ADD(eGERR, "Aucune donnée n'a été trouvée."); return false;}
    if(m_lastId != 0) {
        m_where += GFORMAT(" and _id < %d ", m_lastId);
    }
    if(m_name != "") {
        m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
    }
    if(!searchNextData()) return false;
    return true;
}
//===============================================
bool GQueryType::onDeleteQueryType() {
    if(m_id == 0) {GERROR_ADD(eGERR, "L'identifiant de la donnée est obligatoire."); return false;}
    if(!deleteData()) return false;
    m_logs.addLog("La donnée a bien été supprimée.");
    return true;
}
//===============================================
bool GQueryType::saveData() {
    if(m_id == 0) {
        if(!insertData()) return false;
    }
    else {
        if(!updateData()) return false;
    }
    return true;
}
//===============================================
bool GQueryType::searchData() {
    clearMap();
    GMySQL lMySQL;
    GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _query_type "
            " %s "
            " order by _name asc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));

    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GQueryType* lObj = new GQueryType;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        add(lObj);
    }

    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;

    if(m_hasData) {
        GQueryType* lObj = (GQueryType*)back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GQueryType::searchNextData() {
    clearMap();
    GMySQL lMySQL;
    GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _query_type "
            " %s "
            " order by _id desc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GQueryType* lObj = new GQueryType;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        add(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GQueryType* lObj = (GQueryType*)back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GQueryType::deleteData() {
    if(m_id == 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " delete from _query_type "
            " where 1 = 1 "
            " and _id = %d "
            "", m_id
    ))) return false;
    return true;
}
//===============================================
bool GQueryType::countSearch() {
    GMySQL lMySQL;
    m_dataCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _query_type "
            " %s "
            "", m_where.c_str()
    )).toInt();
    return true;
}
//===============================================
bool GQueryType::insertData() {
    if(m_id != 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " insert into _query_type "
            " ( _name ) "
            " values ( '%s' ) "
            "", m_name.c_str()
    ))) return false;
    m_id = lMySQL.getId();
    return true;
}
//===============================================
bool GQueryType::updateData() {
    if(m_id == 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _query_type set "
            " _name = '%s' "
            " where _id = %d "
            "", m_name.c_str()
            , m_id
    ))) return false;
    return true;
}
//===============================================

