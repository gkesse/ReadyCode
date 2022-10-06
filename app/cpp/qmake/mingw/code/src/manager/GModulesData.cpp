//===============================================
#include "GModulesData.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GModulesData::GModulesData()
: GSearch() {
    m_id = 0;
    m_modulesId = 0;
    m_tableWidget = new GTableWidgetUi;
}
//===============================================
GModulesData::~GModulesData() {
    delete m_tableWidget;
}
//===============================================
GObject* GModulesData::clone() const {
    return new GModulesData;
}
//===============================================
GString GModulesData::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "module_id", m_modulesId);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "value", m_value);
    lDom.addData(_code, m_map);
    lDom.loadData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModulesData::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_modulesId = lDom.getData(_code, "module_id").toInt();
    m_name = lDom.getData(_code, "name");
    m_value = lDom.getData(_code, "value");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModulesData::setModulesData(const GModulesData& _modules) {
    m_id = _modules.m_id;
    m_name = _modules.m_name;
    m_value = _modules.m_value;
}
//===============================================
void GModulesData::setModulesData(GModulesData* _modules) {
    setModulesData(*_modules);
}
//===============================================
void GModulesData::setModulesData(int _index) {
    if(_index < (int)m_map.size()) {
        GModulesData* lModules = (GModulesData*)m_map.at(_index);
        setModulesData(lModules);
    }
    clearMap(m_map);
}
//===============================================
void GModulesData::setModulesId(int _modulesId) {
    m_modulesId = _modulesId;
}
//===============================================
void GModulesData::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
int GModulesData::getId() const {
    return m_id;
}
//===============================================
GString GModulesData::getName() const {
    return m_name;
}
//===============================================
void GModulesData::saveModulesData() {
    GString lData = serialize();
    lData = GCALL_SERVER("modules_data", "save_modules_data", lData);
    deserialize(lData);
}
//===============================================
void GModulesData::searchModulesData() {
    GString lData = serialize();
    lData = GCALL_SERVER("modules_data", "search_modules_data", lData);
    deserialize(lData);
}
//===============================================
void GModulesData::deleteModulesData() {
    GString lData = serialize();
    lData = GCALL_SERVER("modules_data", "delete_modules_data", lData);
    deserialize(lData);
}
//===============================================
void GModulesData::onNextData() {
    clearMap(m_map);
    GString lData = serialize();
    lData = GCALL_SERVER("modules_data", "search_next_modules_data", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModulesData::showList() {
    if(m_map.size() == 0) {
        setModulesData(GModulesData());
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
        GModulesData* lModulesData = (GModulesData*)m_map.at(i);
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
bool GModulesData::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModulesData* lModulesData = (GModulesData*)m_map.at(i);
        int lId = lModulesData->m_id;
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lId, lModulesData->m_id);
        m_tableWidget->addCol(1, lId, lModulesData->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
