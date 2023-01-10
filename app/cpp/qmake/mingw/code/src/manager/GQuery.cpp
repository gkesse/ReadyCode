//===============================================
#include "GQuery.h"
#include "GCode.h"
#include "GBase64.h"
#include "GClient.h"
//===============================================
GQuery::GQuery()
: GSearch() {
    m_typeId = 0;
    m_defaultId = 0;
}
//===============================================
GQuery::~GQuery() {

}
//===============================================
GObject* GQuery::clone() const {
    return new GQuery;
}
//===============================================
GString GQuery::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "type_id", m_typeId);
    lDom.addData(_code, "default_id", m_defaultId);
    lDom.addData(_code, "type_name", m_typeName);
    lDom.addData(_code, "emission", m_emission.toBase64(), true);
    lDom.addData(_code, "reception", m_reception.toBase64(), true);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
void GQuery::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_typeId = lDom.getData(_code, "default_id").toInt();
    m_defaultId = lDom.getData(_code, "type_id").toInt();
    m_typeName = lDom.getData(_code, "type_name");
    m_emission = lDom.getData(_code, "emission").fromBase64();
    m_reception = lDom.getData(_code, "reception").fromBase64();
}
//===============================================
void GQuery::setTypeId(int _typeId) {
    m_typeId = _typeId;
}
//===============================================
void GQuery::setTypeName(const GString& _typeName) {
    m_typeName = _typeName;
}
//===============================================
void GQuery::setEmission(const GString& _emission) {
    m_emission = _emission;
}
//===============================================
void GQuery::setReception(const GString& _reception) {
    m_reception = _reception;
}
//===============================================
int GQuery::getTypeId() const {
    return m_typeId;
}
//===============================================
GString GQuery::getTypeName() const {
    return m_typeName;
}
//===============================================
GString GQuery::getEmission() const {
    return m_emission;
}
//===============================================
GString GQuery::getReception() const {
    return m_reception;
}
//===============================================
void GQuery::sendQuery() {
    GString lData = serialize();
    lData = GCALL_SERVER("query", "send_query", lData);
    deserialize(lData);
}
//===============================================
void GQuery::saveTypeQuery() {
    GString lData = serialize();
    lData = GCALL_SERVER("query", "save_type_query", lData);
    deserialize(lData);
}
//===============================================
void GQuery::searchTypeQuery() {
    GString lData = serialize();
    lData = GCALL_SERVER("query", "search_type_query", lData);
    deserialize(lData);
}
//===============================================
void GQuery::deleteTypeQuery() {
    GString lData = serialize();
    lData = GCALL_SERVER("query", "delete_type_query", lData);
    deserialize(lData);
}
//===============================================
