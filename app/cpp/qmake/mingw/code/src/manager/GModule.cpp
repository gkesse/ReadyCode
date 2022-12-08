//===============================================
#include "GModule.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GModule::GModule(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_tableWidget.reset(new GTableWidgetUi);
}
//===============================================
GModule::~GModule() {
    clearMap();
}
//===============================================
GObject* GModule::clone() const {
    return new GModule;
}
//===============================================
GString GModule::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, m_map, this);
    lDom.addData(GSearch::serialize(), this);
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
void GModule::setModule(const std::shared_ptr<GModule>& _module) {
    setModule(_module.get());
}
//===============================================
void GModule::setModule(int _index) {
    if(_index >= 0 && _index < (int)m_map.size()) {
        GModule* lObj = (GModule*)m_map.at(_index);
        setModule(lObj);
    }
    else {
        setModule(GModule());
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
bool GModule::showList() {
    if(m_map.size() == 0) return true;
    if(m_map.size() == 1) {
        setModule(0);
        return true;
    }
    m_tableWidget->setWindowTitle("Liste des modules");
    m_tableWidget->setSize(m_map.size(), 1);
    m_tableWidget->setHeader(0, "nom");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModule* lObj = (GModule*)m_map.at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->setData(i, 0, lKey, lObj->m_name);
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        GModule lObj;
        lObj.deserialize(m_tableWidget->getKey());
        setModule(lObj);
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
        GModule* lObj = (GModule*)m_map.at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lKey, lObj->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
