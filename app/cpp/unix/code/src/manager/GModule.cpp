//===============================================
#include "GMySQL.h"
#include "GCode.h"
#include "GModule.h"
#include "GLog.h"
//===============================================
GModule::GModule(const GString& _code)
: GSearch(_code) {
    m_id = 0;
}
//===============================================
GModule::~GModule() {
    clearMap();
}
//===============================================
GObject* GModule::clone() const {
    return new GModule;
}
//===============================================
GString GModule::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, m_map);
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModule::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModule::setId(int _id) {
    m_id = _id;
}
//===============================================
int GModule::getId() const {
    return m_id;
}
//===============================================
bool GModule::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_methodName == "save_module") {
        onSaveModule();
    }
    else if(m_methodName == "search_module") {
        onSearchModule();
    }
    else if(m_methodName == "search_next_module") {
        onSearchNextModule();
    }
    else if(m_methodName == "delete_module") {
        onDeleteModule();
    }
    else {
        GMETHOD_UNKNOWN();
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GModule::onSaveModule() {
    if(m_name == "") {GERROR_ADD(eGERR, "Le nom du module est obligatoire."); return false;}
    if(!saveModule()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de l'enregistrement du module."); return false;}
    GLOG_ADD(eGLOG, "La donnée a bien été enregistrée.");
    return true;
}
//===============================================
bool GModule::onSearchModule() {
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
    if(size() == 0) {GERROR_ADD(eGERR, "Aucun résultat n'a été trouvé."); return false;}
    return true;
}
//===============================================
bool GModule::onSearchNextModule() {
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
bool GModule::onDeleteModule() {
    if(m_id == 0) {GERROR_ADD(eGERR, "L'identifiant de la donnée est obligatoire."); return false;}
    if(!deleteModule()) return false;
    GLOG_ADD(eGLOG, "La donnée a bien été supprimée.");
    return true;
}
//===============================================
bool GModule::saveModule() {
    if(m_id == 0) {
        if(!insertModule()) return false;
    }
    else {
        if(!updateModule()) return false;
    }
    return true;
}
//===============================================
bool GModule::searchModule() {
    clearMap();
    GMySQL lMySQL;
    GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _module "
            " %s "
            " order by _name asc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModule* lObj = new GModule;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        add(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModule* lObj = (GModule*)back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GModule::searchModuleId() {
    clearMap();
    GMySQL lMySQL;
    GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _module "
            " where 1 = 1 "
            " and _id = %d "
            "", m_id
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        m_id = lDataRow.at(j++).toInt();
        m_name = lDataRow.at(j++);
        break;
    }
    return true;
}
//===============================================
bool GModule::searchNextModule() {
    clearMap();
    GMySQL lMySQL;
    GMaps lDataMap = lMySQL.readMap(GFORMAT(""
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
        GModule* lObj = new GModule;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        add(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModule* lObj = (GModule*)back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GModule::deleteModule() {
    if(m_id == 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " delete from _module "
            " where 1 = 1 "
            " and _id = %d "
            "", m_id
    ))) return false;
    return true;
}
//===============================================
bool GModule::countSearch() {
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
bool GModule::insertModule() {
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
bool GModule::updateModule() {
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

