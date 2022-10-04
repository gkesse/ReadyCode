//===============================================
#include "GModules.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GModules::GModules()
: GModule() {
    m_id = 0;
    m_tableWidget = new GTableWidgetUi;
}
//===============================================
GModules::~GModules() {
    delete m_tableWidget;
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
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModules::assign(const GModules& _modules) {
    m_id = _modules.m_id;
    m_name = _modules.m_name;
}
//===============================================
void GModules::assign(GModules* _modules) {
    assign(*_modules);
}
//===============================================
void GModules::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
GString GModules::getName() const {
    return m_name;
}
//===============================================
void GModules::createModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "create_module", lData);
    deserialize(lData);
}
//===============================================
void GModules::searchModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "search_module", lData);
    deserialize(lData);
}
//===============================================
void GModules::deleteModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "delete_module", lData);
    deserialize(lData);
}
//===============================================
bool GModules::showList() {
    if(m_map.size() == 0) {
        assign(GModules());
        GERROR_ADD(eGERR, "La réponse est vide.");
        return false;
    }
    else if(m_map.size() == 1) {
        GModules* lModules = (GModules*)m_map.at(0);
        assign(lModules);
        clearMap(m_map);
        return true;
    }
    m_tableWidget->setWindowTitle("Liste des modules");
    m_tableWidget->exec();
    clearMap(m_map);
    return true;
}
//===============================================
