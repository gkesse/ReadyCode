//===============================================
#include "GModules.h"
#include "GLog.h"
#include "GCode2.h"
#include "GServer.h"
#include "GMySQL2.h"
//===============================================
GModules::GModules()
: GModule2() {
    m_id = 0;
}
//===============================================
GModules::~GModules() {

}
//===============================================
GObject2* GModules::clone() const {
    return new GModules;
}
//===============================================
GString GModules::serialize(const GString& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    return lDom.toString();
}
//===============================================
bool GModules::deserialize(const GString& _data, const GString& _code) {
    GModule2::deserialize(_data);
    GCode2 lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    return true;
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
bool GModules::createModule() {
    if(!insertModule()) return false;
    return true;
}
//===============================================
bool GModules::insertModule() {
    if(m_id != 0) return false;
    GMySQL2 lMySQL2;
    if(!lMySQL2.execQuery(GFORMAT(""
            " insert into _module "
            " ( _name ) "
            " values ( '%s' ) "
            "", m_name.c_str()
    ))) return false;
    m_id = lMySQL2.getId();
    return true;
}
//===============================================

