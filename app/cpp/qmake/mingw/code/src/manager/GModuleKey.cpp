//===============================================
#include "GModuleKey.h"
#include "GModule.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GModuleKey::GModuleKey(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_tableWidget.reset(new GTableWidgetUi);
    m_module.reset(new GModule);
}
//===============================================
GModuleKey::~GModuleKey() {
    clearMap(m_map);
}
//===============================================
GObject* GModuleKey::clone() const {
    return new GModuleKey;
}
//===============================================
GString GModuleKey::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "type", m_type);
    lDom.addData(_code, m_map, this);
    lDom.addData(m_module->serialize(), this);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
bool GModuleKey::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    m_module->deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    m_type = lDom.getData(_code, "type");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModuleKey::setModuleKey(const GModuleKey& _moduleKey) {
    m_id = _moduleKey.m_id;
    m_name = _moduleKey.m_name;
    m_type = _moduleKey.m_type;
}
//===============================================
void GModuleKey::setModuleKey(GModuleKey* _moduleKey) {
    setModuleKey(*_moduleKey);
}
//===============================================
void GModuleKey::setModuleKey(int _index) {
    if(_index >= 0 && _index < (int)m_map.size()) {
        GModuleKey* lObj = (GModuleKey*)m_map.at(_index);
        setModuleKey(lObj);
    }
    else {
        setModuleKey(GModuleKey());
    }
    clearMap(m_map);
}
//===============================================
void GModuleKey::setModule(const GModule& _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleKey::setModule(GModule* _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleKey::setModule(const std::shared_ptr<GModule>& _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleKey::setId(int _id) {
    m_id = _id;
}
//===============================================
void GModuleKey::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
void GModuleKey::setType(const GString& _type) {
    m_type = _type;
}
//===============================================
int GModuleKey::getId() const {
    return m_id;
}
//===============================================
GString GModuleKey::getName() const {
    return m_name;
}
//===============================================
GString GModuleKey::getType() const {
    return m_type;
}
//===============================================
void GModuleKey::saveModuleKey() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "save_module_key", lData);
    deserialize(lData);
}
//===============================================
void GModuleKey::searchModuleKey() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "search_module_key", lData);
    deserialize(lData);
}
//===============================================
void GModuleKey::deleteModuleKey() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "delete_module_key", lData);
    deserialize(lData);
}
//===============================================
void GModuleKey::onNextData() {
    clearMap(m_map);
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "search_next_module_key", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModuleKey::showList() {
    if(m_map.size() == 0) {
        setModuleKey(GModuleKey());
        if(!GLOGI->hasErrors()) {
            GSEARCH_AVOID();
        }
        return false;
    }
    else if(m_map.size() == 1) {
        setModuleKey(0);
        return true;
    }
    m_tableWidget->setWindowTitle("Liste des données par module");
    m_tableWidget->setSize(m_map.size(), 3);
    m_tableWidget->setHeader(0, "module");
    m_tableWidget->setHeader(1, "nom");
    m_tableWidget->setHeader(2, "valeur");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleKey* lObj = (GModuleKey*)m_map.at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->setData(i, 0, lKey, m_module->getName());
        m_tableWidget->setData(i, 1, lKey, lObj->m_name);
        m_tableWidget->setData(i, 2, lKey, lObj->m_type);
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        GModuleKey lObj;
        lObj.deserialize(m_tableWidget->getKey());
        setModuleKey(lObj);
    }
    return true;
}
//===============================================
bool GModuleKey::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleKey* lObj = (GModuleKey*)m_map.at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lKey, m_module->getName());
        m_tableWidget->addCol(1, lKey, lObj->m_name);
        m_tableWidget->addCol(2, lKey, lObj->m_type);
    }
    clearMap(m_map);
    return true;
}
//===============================================
