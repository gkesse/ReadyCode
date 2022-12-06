//===============================================
#include "GModuleType.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GModuleType::GModuleType(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_tableWidget.reset(new GTableWidgetUi);
}
//===============================================
GModuleType::~GModuleType() {
    clearMap(m_map);
}
//===============================================
GObject* GModuleType::clone() const {
    return new GModuleType;
}
//===============================================
GString GModuleType::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, m_map, this);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
bool GModuleType::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModuleType::setModuleType(const GModuleType& _moduleType) {
    m_id = _moduleType.m_id;
    m_name = _moduleType.m_name;
}
//===============================================
void GModuleType::setModuleType(GModuleType* _moduleType) {
    setModuleType(*_moduleType);
}
//===============================================
void GModuleType::setModuleType(const std::shared_ptr<GModuleType>& _moduleType) {
    setModuleType(_moduleType.get());
}
//===============================================
void GModuleType::setModuleType(int _index) {
    if(_index >= 0 && _index < (int)m_map.size()) {
        GModuleType* lObj = (GModuleType*)m_map.at(_index);
        setModuleType(lObj);
    }
    clearMap(m_map);
}
//===============================================
void GModuleType::setId(int _id) {
    m_id = _id;
}
//===============================================
void GModuleType::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
int GModuleType::getId() const {
    return m_id;
}
//===============================================
GString GModuleType::getName() const {
    return m_name;
}
//===============================================
void GModuleType::loadModuleType() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_type", "load_module_type", lData);
    deserialize(lData);
}
//===============================================
void GModuleType::saveModuleType() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_type", "save_module_type", lData);
    deserialize(lData);
}
//===============================================
void GModuleType::searchModuleType() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_type", "search_module_type", lData);
    deserialize(lData);
}
//===============================================
void GModuleType::deleteModuleType() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_type", "delete_module_type", lData);
    deserialize(lData);
}
//===============================================
void GModuleType::loadComboBox(QComboBox* _comboBox) {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleType* lObj = (GModuleType*)m_map.at(i);
        int lId = lObj->getId();
        GString lType = lObj->getName();
        _comboBox->addItem(lType.c_str(), lId);
    }
}
//===============================================
bool GModuleType::showList() {
    if(m_map.size() == 0) return true;
    if(m_map.size() == 1) {
        setModuleType(0);
        return true;
    }
    m_tableWidget->setWindowTitle("Liste des modules");
    m_tableWidget->setSize(m_map.size(), 1);
    m_tableWidget->setHeader(0, "nom");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleType* lObj = (GModuleType*)m_map.at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->setData(i, 0, lKey, lObj->m_name);
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        GModuleType lObj;
        lObj.deserialize(m_tableWidget->getKey());
        setModuleType(lObj);
    }
    return true;
}
//===============================================
void GModuleType::onNextData() {
    clearMap(m_map);
    GString lData = serialize();
    lData = GCALL_SERVER("module_type", "search_next_module_type", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModuleType::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleType* lObj = (GModuleType*)m_map.at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lKey, lObj->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
