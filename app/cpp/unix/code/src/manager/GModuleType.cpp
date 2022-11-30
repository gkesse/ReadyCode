//===============================================
#include "GMySQL.h"
#include "GCode.h"
#include "GModuleType.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GModuleType::GModuleType(const GString& _code)
: GSearch(_code) {
    m_id = 0;
}
//===============================================
GModuleType::~GModuleType() {
    clearMap(m_map);
}
//===============================================
GObject* GModuleType::clone() const {
    return new GModuleType;
}
//===============================================
GString GModuleType::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, m_map);
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleType::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
int GModuleType::getId() const {
    return m_id;
}
//===============================================
bool GModuleType::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_methodName == "save_module_type") {
        onSaveModuleType();
    }
    else if(m_methodName == "search_module_type") {
        onSearchModuleType();
    }
    else if(m_methodName == "search_next_module_type") {
        onSearchNextModuleType();
    }
    else {
        GMETHOD_UNKNOWN();
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GModuleType::onSaveModuleType() {
    if(m_name == "") {GERROR_ADD(eGERR, "Le nom est obligatoire."); return false;}
    if(!saveModuleType()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de l'enregistrement du module."); return false;}
    GLOG_ADD(eGLOG, "Le module a bien été enregistré.");
    return true;
}
//===============================================
bool GModuleType::onSearchModuleType() {
    if(m_id != 0) {
        m_where += GFORMAT(" and _id = %d ", m_id);
    }
    else {
        if(m_name != "") {
            m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
        }
    }
    if(!countSearch()) return false;
    if(!searchModuleType()) return false;
    return true;
}
//===============================================
bool GModuleType::onSearchNextModuleType() {
    if(!m_hasData) {GERROR_ADD(eGERR, "Aucune donnée n'a été trouvée."); return false;}
    if(m_lastId != 0) {
        m_where += GFORMAT(" and _id < %d ", m_lastId);
    }
    if(m_name != "") {
        m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
    }
    if(!searchNextModuleType()) return false;
    return true;
}
//===============================================
bool GModuleType::saveModuleType() {
    if(m_id == 0) {
        if(!insertModuleType()) return false;
    }
    else {
        if(!updateModuleType()) {
            onSearchModuleType();
            return false;
        }
    }
    return true;
}
//===============================================
bool GModuleType::searchModuleType() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _module_type "
            " %s "
            " order by _name asc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    clearMap(m_map);
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleType* lObj = new GModuleType;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        m_map.push_back(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleType* lObj = (GModuleType*)m_map.back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GModuleType::searchNextModuleType() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _module_type "
            " %s "
            " order by _name asc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleType* lObj = new GModuleType;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        m_map.push_back(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleType* lObj = (GModuleType*)m_map.back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GModuleType::countSearch() {
    GMySQL lMySQL;
    m_dataCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _module_type "
            " %s "
            "", m_where.c_str()
    )).toInt();
    return true;
}
//===============================================
bool GModuleType::insertModuleType() {
    if(m_id != 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " insert into _module_type "
            " ( _name ) "
            " values ( '%s' ) "
            "", m_name.c_str()
    ))) return false;
    m_id = lMySQL.getId();
    return true;
}
//===============================================
bool GModuleType::updateModuleType() {
    if(m_id == 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module_type set "
            " _name = '%s' "
            " where _id = %d "
            "", m_name.c_str()
            , m_id
    ))) return false;
    return true;
}
//===============================================

