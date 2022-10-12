//===============================================
#include "GModuleData.h"
#include "GModule.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GModuleData::GModuleData()
: GSearch() {
    m_id = 0;
    m_tableWidget = new GTableWidgetUi;
    m_module = new GModule;
}
//===============================================
GModuleData::~GModuleData() {
    delete m_tableWidget;
    delete m_module;
}
//===============================================
GObject* GModuleData::clone() const {
    return new GModuleData;
}
//===============================================
GString GModuleData::serialize() const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(m_codeName, "id", m_id);
    lDom.addData(m_codeName, "name", m_name);
    lDom.addData(m_codeName, "value", m_value);
    lDom.addData(m_codeName, m_map);
    lDom.loadData(m_module->serialize());
    lDom.loadData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleData::deserialize(const GString& _data) {
    GSearch::deserialize(_data);
    m_module->deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(m_codeName, "id").toInt();
    m_name = lDom.getData(m_codeName, "name");
    m_value = lDom.getData(m_codeName, "value");
    lDom.getData(m_codeName, m_map, this);
    return true;
}
//===============================================
void GModuleData::setModuleData(const GModuleData& _module) {
    m_id = _module.m_id;
    m_name = _module.m_name;
    m_value = _module.m_value;
}
//===============================================
void GModuleData::setModuleData(GModuleData* _module) {
    setModuleData(*_module);
}
//===============================================
void GModuleData::setModuleData(int _index) {
    if(_index < (int)m_map.size()) {
        GModuleData* lModules = (GModuleData*)m_map.at(_index);
        setModuleData(lModules);
    }
    clearMap(m_map);
}
//===============================================
void GModuleData::setModule(GModule* _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleData::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
void GModuleData::setValue(const GString& _value) {
    m_value = _value;
}
//===============================================
int GModuleData::getId() const {
    return m_id;
}
//===============================================
GString GModuleData::getName() const {
    return m_name;
}
//===============================================
GString GModuleData::getValue() const {
    return m_value;
}
//===============================================
void GModuleData::saveModuleData() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_data", "save_module_data", lData);
    deserialize(lData);
}
//===============================================
void GModuleData::searchModuleData() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_data", "search_module_data", lData);
    deserialize(lData);
}
//===============================================
void GModuleData::deleteModuleData() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_data", "delete_module_data", lData);
    deserialize(lData);
}
//===============================================
void GModuleData::onNextData() {
    clearMap(m_map);
    GString lData = serialize();
    lData = GCALL_SERVER("module_data", "search_next_module_data", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModuleData::showList() {
    if(m_map.size() == 0) {
        setModuleData(GModuleData());
        if(!GLOGI->hasErrors()) {
            GSEARCH_AVOID();
        }
        return false;
    }
    else if(m_map.size() == 1) {
        setModuleData(0);
        return true;
    }
    m_tableWidget->setWindowTitle("Liste des données par module");
    m_tableWidget->setSize(m_map.size(), 4);
    m_tableWidget->setHeader(0, "id");
    m_tableWidget->setHeader(1, "module");
    m_tableWidget->setHeader(2, "nom");
    m_tableWidget->setHeader(3, "valeur");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleData* lModulesData = (GModuleData*)m_map.at(i);
        int lId = lModulesData->m_id;
        m_tableWidget->setData(i, 0, lId, lModulesData->m_id);
        m_tableWidget->setData(i, 1, lId, m_module->getName());
        m_tableWidget->setData(i, 2, lId, lModulesData->m_name);
        m_tableWidget->setData(i, 3, lId, lModulesData->m_value);
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        m_id = m_tableWidget->getKey().toInt();
        setSearch(GSearch());
        searchModuleData();
        setModuleData(0);
    }
    return true;
}
//===============================================
bool GModuleData::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleData* lModulesData = (GModuleData*)m_map.at(i);
        int lId = lModulesData->m_id;
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lId, lModulesData->m_id);
        m_tableWidget->addCol(1, lId, lModulesData->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
