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
    m_moduleId = 0;
    m_tableWidget.reset(new GTableWidgetUi);
    m_module.reset(new GModule);
}
//===============================================
GModuleData::~GModuleData() {
    clearMap();
}
//===============================================
GObject* GModuleData::clone() const {
    return new GModuleData;
}
//===============================================
GString GModuleData::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "module_id", m_moduleId);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "value", m_value);
    lDom.addData(_code, m_map, this);
    lDom.addData(m_module->serialize(), this);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
bool GModuleData::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    m_module->deserialize(_data);
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
void GModuleData::setModuleData(const GModuleData& _moduleData) {
    m_id = _moduleData.m_id;
    m_moduleId = _moduleData.m_moduleId;
    m_name = _moduleData.m_name;
    m_value = _moduleData.m_value;
}
//===============================================
void GModuleData::setModuleData(GModuleData* _moduleData) {
    setModuleData(*_moduleData);
}
//===============================================
void GModuleData::setModuleData(int _index) {
    if(_index >= 0 && _index < (int)m_map.size()) {
        GModuleData* lObj = (GModuleData*)m_map.at(_index);
        setModuleData(lObj);
    }
    clearMap(m_map);
}
//===============================================
void GModuleData::setModule(const GModule& _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleData::setModule(GModule* _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleData::setModule(const std::shared_ptr<GModule>& _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleData::setId(int _id) {
    m_id = _id;
}
//===============================================
void GModuleData::setModuleId(int _moduleId) {
    m_moduleId = _moduleId;
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
int GModuleData::getModuleId() const {
    return m_moduleId;
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
    if(m_map.size() == 0) return true;
    if(m_map.size() == 1) {
        setModuleData(0);
        return true;
    }
    m_tableWidget->setWindowTitle("Liste des données");
    m_tableWidget->setSize(m_map.size(), 3);
    m_tableWidget->setHeader(0, "module");
    m_tableWidget->setHeader(1, "nom");
    m_tableWidget->setHeader(2, "valeur");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleData* lObj = (GModuleData*)m_map.at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->setData(i, 0, lKey, m_module->getName());
        m_tableWidget->setData(i, 1, lKey, lObj->m_name);
        m_tableWidget->setData(i, 2, lKey, lObj->m_value);
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        GModuleData lObj;
        lObj.deserialize(m_tableWidget->getKey());
        setModuleData(lObj);
    }
    return true;
}
//===============================================
bool GModuleData::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleData* lObj = (GModuleData*)m_map.at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lKey, m_module->getName());
        m_tableWidget->addCol(1, lKey, lObj->m_name);
        m_tableWidget->addCol(2, lKey, lObj->m_value);
    }
    clearMap(m_map);
    return true;
}
//===============================================
