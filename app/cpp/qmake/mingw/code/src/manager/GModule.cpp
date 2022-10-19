//===============================================
#include "GModule.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
#include "GTableWidget.h"
#include "GTableWidgetFr.h"
//===============================================
GModule::GModule(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_tableWidget = new GTableWidgetUi;
}
//===============================================
GModule::~GModule() {
    delete m_tableWidget;
    clearMap(m_map);
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
void GModule::setId(int _id) {
    m_id = _id;
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
void GModule::loadModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "load_module", lData);
    deserialize(lData);
}
//===============================================
void GModule::loadModule2() {
    clearMap(m_map);
    for(int i = 0; i < 5; i++) {
        GModule* lObj = new GModule;
        lObj->m_id = i + 1;
        lObj->m_name = GFORMAT("M[%d]", lObj->m_id);
        m_map.push_back(lObj);
    }
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
bool GModule::showModule(GTableWidget* _tableWidget) {
    _tableWidget->setSize(m_map.size(), 2);
    _tableWidget->setHeader(0, "id");
    _tableWidget->setHeader(1, "nom");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModule* lObj = (GModule*)m_map.at(i);
        GString lKey = lObj->serialize();
        _tableWidget->setData(i, 0, lKey, lObj->m_id);
        _tableWidget->setData(i, 1, lKey, lObj->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
bool GModule::showModule2(GTableWidgetFr* _tableWidget) {
    showModule(_tableWidget->getTableWidget());
    return true;
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
void GModule::onNextData() {
    clearMap(m_map);
    GString lData = serialize();
    lData = GCALL_SERVER("module", "search_next_module", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModule::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModule* lModule = (GModule*)m_map.at(i);
        int lId = lModule->m_id;
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lId, lModule->m_id);
        m_tableWidget->addCol(1, lId, lModule->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
