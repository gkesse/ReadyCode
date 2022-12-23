//===============================================
#include "GQueryType.h"
#include "GCode.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GQueryType::GQueryType(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_tableWidget.reset(new GTableWidgetUi);
}
//===============================================
GQueryType::~GQueryType() {

}
//===============================================
GObject* GQueryType::clone() const {
    return new GQueryType;
}
//===============================================
GString GQueryType::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, m_map);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
bool GQueryType::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    lDom.getData(_code, m_map, this);
   return true;
}
//===============================================
void GQueryType::setQueryType(const GQueryType& _queryType) {
    m_id = _queryType.m_id;
    m_name = _queryType.m_name;
}
//===============================================
void GQueryType::setQueryType(GQueryType* _queryType) {
    setQueryType(*_queryType);
}
//===============================================
void GQueryType::setQueryType(int _index) {
    if(_index >= 0 && _index < size()) {
        GQueryType* lObj = (GQueryType*)at(_index);
        setQueryType(lObj);
    }
    clearMap();
}
//===============================================
void GQueryType::setId(int _id) {
    m_id = _id;
}
//===============================================
void GQueryType::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
int GQueryType::getId() const {
    return m_id;
}
//===============================================
GString GQueryType::getName() const {
    return m_name;
}
//===============================================
void GQueryType::saveQueryType() {
    GString lData = serialize();
    lData = GCALL_SERVER("query_type", "save_query_type", lData);
    deserialize(lData);
}
//===============================================
void GQueryType::searchQueryType() {
    GString lData = serialize();
    lData = GCALL_SERVER("query_type", "search_query_type", lData);
    deserialize(lData);
}
//===============================================
void GQueryType::deleteQueryType() {
    GString lData = serialize();
    lData = GCALL_SERVER("query_type", "delete_query_type", lData);
    deserialize(lData);
}
//===============================================
bool GQueryType::showList() {
    if(size() == 0) return true;
    if(size() == 1) {
        setQueryType(0);
        return true;
    }

    m_tableWidget->setWindowTitle("Liste des modules");
    m_tableWidget->setSize(size(), 1);
    m_tableWidget->setHeader(0, "nom");

    for(int i = 0; i < size(); i++) {
        GQueryType* lType = (GQueryType*)at(i);
        GString lKey = lType->serialize();
        m_tableWidget->setData(i, 0, lKey, lType->m_name);
    }

    clearMap();
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();

    if(lOk == QDialog::Accepted) {
        GQueryType lObj;
        lObj.deserialize(m_tableWidget->getKey());
        setQueryType(lObj);
    }
    return true;
}
//===============================================
void GQueryType::onNextData() {
    clearMap();
    GString lData = serialize();
    lData = GCALL_SERVER("module", "search_next_module", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GQueryType::showNextList() {
    for(int i = 0; i < size(); i++) {
        GQueryType* lObj = (GQueryType*)at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lKey, lObj->m_name);
    }
    clearMap();
    return true;
}
//===============================================
