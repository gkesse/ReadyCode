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
    lDom.addData(_code, "module", m_module.toBase64(), true);
    lDom.addData(_code, m_map, this);
    lDom.addData(GSearch::serialize(), this);
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
    m_module = lDom.getData(_code, "module").fromBase64();
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModuleData::setModuleData(const GModuleData& _moduleData) {
    m_id = _moduleData.m_id;
    m_moduleId = _moduleData.m_moduleId;
    m_name = _moduleData.m_name;
    m_value = _moduleData.m_value;
    m_module = _moduleData.m_module;
}
//===============================================
void GModuleData::setModuleData(GModuleData* _moduleData) {
    setModuleData(*_moduleData);
}
//===============================================
void GModuleData::setModuleData(int _index) {
    GModuleData* lObj = (GModuleData*)at(_index);
    setModuleData(lObj);
    clearMap();
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
    clearMap();
    GString lData = serialize();
    lData = GCALL_SERVER("module_data", "search_next_module_data", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModuleData::showList() {
    if(size() == 0) return true;
    if(size() == 1) {
        setModuleData(0);
        return true;
    }

    m_tableWidget->setWindowTitle("Liste des données");
    m_tableWidget->setSize(size(), 3);
    m_tableWidget->setHeader(0, "module");
    m_tableWidget->setHeader(1, "nom");
    m_tableWidget->setHeader(2, "valeur");

    for(int i = 0; i < size(); i++) {
        GModuleData* lData = (GModuleData*)at(i);
        GModule lModule;
        lModule.deserialize(lData->m_module);
        GString lKey = lData->serialize();
        m_tableWidget->setData(i, 0, lKey, lModule.getName());
        m_tableWidget->setData(i, 1, lKey, lData->m_name);
        m_tableWidget->setData(i, 2, lKey, lData->m_value);
    }

    clearMap();
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
    for(int i = 0; i < size(); i++) {
        GModuleData* lObj = (GModuleData*)at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lKey, "m_module->getName()");
        m_tableWidget->addCol(1, lKey, lObj->m_name);
        m_tableWidget->addCol(2, lKey, lObj->m_value);
    }
    clearMap();
    return true;
}
//===============================================
