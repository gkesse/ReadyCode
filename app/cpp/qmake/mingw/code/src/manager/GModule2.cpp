//===============================================
#include "GModule2.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidget.h"
#include "GTableWidgetUi.h"
//===============================================
GModule2::GModule2(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_tableWidget.reset(new GTableWidgetUi);
}
//===============================================
GModule2::~GModule2() {
    clearMap(m_map);
}
//===============================================
GObject* GModule2::clone() const {
    return new GModule2;
}
//===============================================
GString GModule2::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, m_map, this);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
bool GModule2::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModule2::setModule(const GModule2& _module) {
    m_id = _module.m_id;
    m_name = _module.m_name;
}
//===============================================
void GModule2::setModule(GModule2* _module) {
    setModule(*_module);
}
//===============================================
void GModule2::setModule(int _index) {
    if(_index >=0 && _index < (int)m_map.size()) {
        GModule2* lObj = (GModule2*)m_map.at(_index);
        setModule(lObj);
    }
    else {
        setModule(GModule2());
    }
    clearMap(m_map);
}
//===============================================
void GModule2::setId(int _id) {
    m_id = _id;
}
//===============================================
void GModule2::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
int GModule2::getId() const {
    return m_id;
}
//===============================================
GString GModule2::getName() const {
    return m_name;
}
//===============================================
void GModule2::saveModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "save_module", lData);
    deserialize(lData);
}
//===============================================
void GModule2::searchModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "search_module", lData);
    deserialize(lData);
}
//===============================================
void GModule2::deleteModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "delete_module", lData);
    deserialize(lData);
}
//===============================================
bool GModule2::showModule(GTableWidget* _tableWidget) {
    _tableWidget->setSize(m_map.size(), 2);
    _tableWidget->setHeader(0, "id");
    _tableWidget->setHeader(1, "nom");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModule2* lObj = (GModule2*)m_map.at(i);
        GString lKey = lObj->serialize();
        _tableWidget->setData(i, 0, lKey, lObj->m_id);
        _tableWidget->setData(i, 1, lKey, lObj->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
bool GModule2::showList() {
    if(m_map.size() == 0) {
        setModule(GModule2());
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
    m_tableWidget->setSize(m_map.size(), 1);
    m_tableWidget->setHeader(0, "nom");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModule2* lModule = (GModule2*)m_map.at(i);
        GString lKey = lModule->serialize();
        m_tableWidget->setData(i, 0, lKey, lModule->m_name);
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        GModule2 lObj;
        lObj.deserialize(m_tableWidget->getKey());
        setModule(lObj);
    }
    return true;
}
//===============================================
void GModule2::onNextData() {
    clearMap(m_map);
    GString lData = serialize();
    lData = GCALL_SERVER("module", "search_next_module", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModule2::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModule2* lModule = (GModule2*)m_map.at(i);
        GString lKey = lModule->serialize();
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lKey, lModule->m_id);
        m_tableWidget->addCol(1, lKey, lModule->m_name);
    }
    clearMap(m_map);
    return true;
}
//===============================================
