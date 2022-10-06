//===============================================
#include "GMySQL.h"
#include "GCode.h"
#include "GModules.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GModules::GModules()
: GSearch() {
    initModules();
}
//===============================================
GModules::~GModules() {

}
//===============================================
GObject* GModules::clone() const {
    return new GModules;
}
//===============================================
GString GModules::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, m_map);
    lDom.loadData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModules::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModules::initModules() {
    m_id = 0;
    m_where = " where 1 = 1 ";
}
//===============================================
bool GModules::onModule() {
    deserialize(m_server->getRequest());
    if(m_method == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_method == "save_module") {
        onSaveModule();
    }
    else if(m_method == "search_module") {
        onSearchModule();
    }
    else if(m_method == "search_next_module") {
        onSearchNextModule();
    }
    else {
        GMETHOD_UNKNOWN();
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GModules::onSaveModule() {
    if(m_id != 0) {GERROR_ADD(eGERR, "Le module est déjà enregistré."); return false;}
    if(m_name == "") {GERROR_ADD(eGERR, "Le nom du module est obligatoire."); return false;}
    if(!saveModule()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de la création du module."); return false;}
    GLOG_ADD(eGLOG, "Le module a bien été enregistré.");
    return true;
}
//===============================================
bool GModules::onSearchModule() {
    if(m_id != 0) {
        m_where += GFORMAT(" and _id = %d ", m_id);
    }
    else {
        if(m_name != "") {
            m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
        }
    }
    if(!countSearch()) return false;
    if(!searchModule()) return false;
    return true;
}
//===============================================
bool GModules::onSearchNextModule() {
    if(!m_hasData) {GERROR_ADD(eGERR, "Aucune donnée n'a été trouvée."); return false;}
    if(m_lastId != 0) {
        m_where += GFORMAT(" and _id < %d ", m_lastId);
    }
    if(m_name != "") {
        m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
    }
    if(!searchNextModule()) return false;
    return true;
}
//===============================================
bool GModules::saveModule() {
    if(m_id == 0) {
        if(!insertModule()) return false;
    }
    else {
        if(!updateModule()) return false;
    }
    return true;
}
//===============================================
bool GModules::searchModule() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _module "
            " %s "
            " order by _id desc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModules* lModule = new GModules;
        lModule->m_id = lDataRow.at(j++).toInt();
        lModule->m_name = lDataRow.at(j++);
        m_map.push_back(lModule);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModules* lModule = (GModules*)m_map.back();
        m_lastId = lModule->m_id;
    }
    return true;
}
//===============================================
bool GModules::searchNextModule() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _module "
            " %s "
            " order by _id desc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModules* lModule = new GModules;
        lModule->m_id = lDataRow.at(j++).toInt();
        lModule->m_name = lDataRow.at(j++);
        m_map.push_back(lModule);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModules* lModule = (GModules*)m_map.back();
        m_lastId = lModule->m_id;
    }
    return true;
}
//===============================================
bool GModules::countSearch() {
    GMySQL lMySQL;
    m_dataCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _module "
            " %s "
            "", m_where.c_str()
    )).toInt();
    return true;
}
//===============================================
bool GModules::insertModule() {
    if(m_id != 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " insert into _module "
            " ( _name ) "
            " values ( '%s' ) "
            "", m_name.c_str()
    ))) return false;
    m_id = lMySQL.getId();
    return true;
}
//===============================================
bool GModules::updateModule() {
    if(m_id == 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module set "
            " _name = '%s' "
            " where _id = %d "
            "", m_name.c_str()
            , m_id
    ))) return false;
    return true;
}
//===============================================

