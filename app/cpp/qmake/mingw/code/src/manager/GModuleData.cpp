//===============================================
#include "GModuleData.h"
#include "GModule.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GModuleData::GModuleData(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_tableWidget = new GTableWidgetUi;
    m_module = new GModule;
}
//===============================================
GModuleData::~GModuleData() {
    delete m_tableWidget;
    delete m_module;
    clearMap(m_map);
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
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "value", m_value);
    lDom.addData(_code, m_map);
    lDom.addData(m_module->serialize());
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleData::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    m_module->deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    m_value = lDom.getData(_code, "value");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModuleData::setModuleData(const GModuleData& _moduleData) {
    m_id = _moduleData.m_id;
    m_name = _moduleData.m_name;
    m_value = _moduleData.m_value;
}
//===============================================
void GModuleData::setModuleData(GModuleData* _moduleData) {
    setModuleData(*_moduleData);
}
//===============================================
void GModuleData::setModuleData(int _index) {
    if(_index < (int)m_map.size()) {
        GModuleData* lObj = (GModuleData*)m_map.at(_index);
        setModuleData(lObj);
    }
    clearMap(m_map);
}
//===============================================
void GModuleData::setModule(const GModule* _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleData::setModule(const std::shared_ptr<GModule>& _module) {
    m_module->setModule(_module.get());
}
//===============================================
void GModuleData::setId(int _id) {
    m_id = _id;
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
        GModuleData* lModuleData = (GModuleData*)m_map.at(i);
        int lId = lModuleData->m_id;
        m_tableWidget->setData(i, 0, lId, lModuleData->m_id);
        m_tableWidget->setData(i, 1, lId, m_module->getName());
        m_tableWidget->setData(i, 2, lId, lModuleData->m_name);
        m_tableWidget->setData(i, 3, lId, lModuleData->m_value);
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
        GModuleData* lModuleData = (GModuleData*)m_map.at(i);
        int lId = lModuleData->m_id;
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lId, lModuleData->m_id);
        m_tableWidget->addCol(1, lId, lModuleData->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
