//===============================================
#include "GMySQL.h"
#include "GCode.h"
#include "GModules.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GModules::GModules()
: GModule() {
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
    return lDom.toString();
}
//===============================================
bool GModules::deserialize(const GString& _data, const GString& _code) {
    GModule::deserialize(_data);
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
    else if(m_method == "create_module") {
        onCreateModule();
    }
    else if(m_method == "search_module") {
        onSearchModule();
    }
    else {
        GMETHOD_UNKNOWN();
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GModules::onCreateModule() {
    if(m_id != 0) {GERROR_ADD(eGERR, "Le module est déjà enregistré."); return false;}
    if(m_name == "") {GERROR_ADD(eGERR, "Le nom du module est obligatoire."); return false;}
    if(!createModule()) return false;
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
    if(!searchModule()) return false;
    return true;
}
//===============================================
bool GModules::createModule() {
    if(!insertModule()) return false;
    return true;
}
//===============================================
bool GModules::searchModule() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _module "
            " %s "
            "", m_where.c_str()
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModules* lModule = new GModules;
        lModule->m_id = lDataRow.at(j++).toInt();
        lModule->m_name = lDataRow.at(j++);
        m_map.push_back(lModule);
    }
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

