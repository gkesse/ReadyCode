//===============================================
#include "GModuleData.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GModuleData::GModuleData()
: GSearch() {
    m_id = 0;
    m_moduleId = 0;
    m_tableWidget = new GTableWidgetUi;
}
//===============================================
GModuleData::~GModuleData() {
    delete m_tableWidget;
}
//===============================================
GObject* GModuleData::clone() const {
    return new GModuleData;
}
//===============================================
GString GModuleData::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "module_id", m_moduleId);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "value", m_value);
    lDom.addData(_code, m_map);
    lDom.loadData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleData::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_moduleId = lDom.getData(_code, "module_id").toInt();
    m_name = lDom.getData(_code, "name");
    m_value = lDom.getData(_code, "value");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModuleData::setModulesData(const GModuleData& _modules) {
    m_id = _modules.m_id;
    m_name = _modules.m_name;
    m_value = _modules.m_value;
}
//===============================================
void GModuleData::setModulesData(GModuleData* _modules) {
    setModulesData(*_modules);
}
//===============================================
void GModuleData::setModulesData(int _index) {
    if(_index < (int)m_map.size()) {
        GModuleData* lModules = (GModuleData*)m_map.at(_index);
        setModulesData(lModules);
    }
    clearMap(m_map);
}
//===============================================
void GModuleData::setModulesId(int _modulesId) {
    m_moduleId = _modulesId;
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
void GModuleData::saveModulesData() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_data", "save_module_data", lData);
    deserialize(lData);
}
//===============================================
void GModuleData::searchModulesData() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_data", "search_module_data", lData);
    deserialize(lData);
}
//===============================================
void GModuleData::deleteModulesData() {
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
        setModulesData(GModuleData());
        if(!GLOGI->hasErrors()) {
            GSEARCH_AVOID();
        }
        return false;
    }
    else if(m_map.size() == 1) {
        setModulesData(0);
        return true;
    }
    m_tableWidget->setWindowTitle("Liste des modules");
    m_tableWidget->setSize(m_map.size(), 2);
    m_tableWidget->setHeader(0, "id");
    m_tableWidget->setHeader(1, "nom");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleData* lModulesData = (GModuleData*)m_map.at(i);
        int lId = lModulesData->m_id;
        m_tableWidget->setData(i, 0, lId, lModulesData->m_id);
        m_tableWidget->setData(i, 1, lId, lModulesData->m_name);
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        m_id = m_tableWidget->getKey().toInt();
        setSearch(GSearch());
        searchModulesData();
        setModulesData(0);
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
