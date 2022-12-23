//===============================================
#include "GModuleType.h"
#include "GCode.h"
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
    clearMap();
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
    lDom.addData(_code, m_map);
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
void GModuleType::setModuleType(int _index) {
    GModuleType* lObj = (GModuleType*)at(_index);
    setModuleType(lObj);
    clearMap();
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
    for(int i = 0; i < size(); i++) {
        GModuleType* lType = (GModuleType*)at(i);
        _comboBox->addItem(lType->getName().c_str(), lType->getId());
    }
}
//===============================================
bool GModuleType::showList() {
    if(size() == 0) return true;
    if(size() == 1) {
        setModuleType(0);
        return true;
    }

    m_tableWidget->setWindowTitle("Liste des modules");
    m_tableWidget->setSize(size(), 1);
    m_tableWidget->setHeader(0, "nom");

    for(int i = 0; i < size(); i++) {
        GModuleType* lType = (GModuleType*)at(i);
        GString lKey = lType->serialize();
        m_tableWidget->setData(i, 0, lKey, lType->m_name);
    }

    clearMap();
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();

    if(lOk == QDialog::Accepted) {
        GModuleType lType;
        lType.deserialize(m_tableWidget->getKey());
        setModuleType(lType);
    }
    return true;
}
//===============================================
void GModuleType::onNextData() {
    clearMap();
    GString lData = serialize();
    lData = GCALL_SERVER("module_type", "search_next_module_type", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModuleType::showNextList() {
    for(int i = 0; i < size(); i++) {
        GModuleType* lType = (GModuleType*)at(i);
        GString lKey = lType->serialize();
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lKey, lType->m_name);
    }
    clearMap();
    return true;
}
//===============================================
