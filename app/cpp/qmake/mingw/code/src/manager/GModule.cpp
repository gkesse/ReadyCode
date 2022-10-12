//===============================================
#include "GModule.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GModule::GModule()
: GSearch() {
    m_id = 0;
    m_tableWidget = new GTableWidgetUi;
}
//===============================================
GModule::~GModule() {
    delete m_tableWidget;
}
//===============================================
GObject* GModule::clone() const {
    return new GModule;
}
//===============================================
GString GModule::serialize() const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(m_codeName, "id", m_id);
    lDom.addData(m_codeName, "name", m_name);
    lDom.addData(m_codeName, m_map);
    lDom.loadData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModule::deserialize(const GString& _data) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(m_codeName, "id").toInt();
    m_name = lDom.getData(m_codeName, "name");
    lDom.getData(m_codeName, m_map, this);
    return true;
}
//===============================================
void GModule::setModule(const GModule& _module) {
    m_id = _module.m_id;
    m_name = _module.m_name;
}
//===============================================
void GModule::setModule(GModule* _module) {
    setModule(*_module);
}
//===============================================
void GModule::setModule(int _index) {
    if(_index < (int)m_map.size()) {
        GModule* lModules = (GModule*)m_map.at(_index);
        setModule(lModules);
    }
    clearMap(m_map);
}
//===============================================
void GModule::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
int GModule::getId() const {
    return m_id;
}
//===============================================
GString GModule::getName() const {
    return m_name;
}
//===============================================
void GModule::saveModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "save_module", lData);
    deserialize(lData);
}
//===============================================
void GModule::searchModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "search_module", lData);
    deserialize(lData);
}
//===============================================
void GModule::deleteModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "delete_module", lData);
    deserialize(lData);
}
//===============================================
void GModule::onNextData() {
    clearMap(m_map);
    GString lData = serialize();
    lData = GCALL_SERVER("module", "search_next_module", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModule::showList() {
    if(m_map.size() == 0) {
        setModule(GModule());
        if(!GLOGI->hasErrors()) {
            GSEARCH_AVOID();
        }
        return false;
    }
    else if(m_map.size() == 1) {
        setModule(0);
        return true;
    }
    m_tableWidget->setWindowTitle("Liste des modules");
    m_tableWidget->setSize(m_map.size(), 2);
    m_tableWidget->setHeader(0, "id");
    m_tableWidget->setHeader(1, "nom");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModule* lModule = (GModule*)m_map.at(i);
        int lId = lModule->m_id;
        m_tableWidget->setData(i, 0, lId, lModule->m_id);
        m_tableWidget->setData(i, 1, lId, lModule->m_name);
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        m_id = m_tableWidget->getKey().toInt();
        setSearch(GSearch());
        searchModule();
        setModule(0);
    }
    return true;
}
//===============================================
bool GModule::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModule* lModules = (GModule*)m_map.at(i);
        int lId = lModules->m_id;
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lId, lModules->m_id);
        m_tableWidget->addCol(1, lId, lModules->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
