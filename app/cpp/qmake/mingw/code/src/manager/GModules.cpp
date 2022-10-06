//===============================================
#include "GModules.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GModules::GModules()
: GSearch() {
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
void GModules::setModules(const GModules& _modules) {
    m_id = _modules.m_id;
    m_name = _modules.m_name;
}
//===============================================
void GModules::setModules(GModules* _modules) {
    setModules(*_modules);
}
//===============================================
void GModules::setModules(int _index) {
    GModules* lModules = (GModules*)m_map.at(_index);
    setModules(lModules);
    clearMap(m_map);
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
void GModules::saveModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("modules", "save_module", lData);
    deserialize(lData);
}
//===============================================
void GModules::searchModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("modules", "search_module", lData);
    deserialize(lData);
}
//===============================================
void GModules::deleteModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("modules", "delete_module", lData);
    deserialize(lData);
}
//===============================================
void GModules::onNextData() {
    clearMap(m_map);
    GString lData = serialize();
    lData = GCALL_SERVER("modules", "search_next_module", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModules::showList() {
    if(m_map.size() == 0) {
        setModules(GModules());
        if(!GLOGI->hasErrors()) {
            GSEARCH_AVOID();
        }
        return false;
    }
    else if(m_map.size() == 1) {
        setModules(0);
        return true;
    }
    m_tableWidget->setWindowTitle("Liste des modules");
    m_tableWidget->setSize(m_map.size(), 2);
    m_tableWidget->setHeader(0, "id");
    m_tableWidget->setHeader(1, "nom");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModules* lModules = (GModules*)m_map.at(i);
        int lId = lModules->m_id;
        m_tableWidget->setData(i, 0, lId, lModules->m_id);
        m_tableWidget->setData(i, 1, lId, lModules->m_name);
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        m_id = m_tableWidget->getKey().toInt();
        setSearch(GSearch());
        searchModule();
        setModules(0);
    }
    return true;
}
//===============================================
bool GModules::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModules* lModules = (GModules*)m_map.at(i);
        int lId = lModules->m_id;
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lId, lModules->m_id);
        m_tableWidget->addCol(1, lId, lModules->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
