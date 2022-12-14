//===============================================
#include "GQueryType.h"
#include "GCode.h"
#include "GClient.h"
#include "GLog.h"
//===============================================
GQueryType::GQueryType(const GString& _code)
: GSearch(_code) {
    m_id = 0;
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
    return true;
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
    lData = GCALL_SERVER("query", "search_query_type", lData);
    deserialize(lData);
}
//===============================================
void GQueryType::deleteQueryType() {
    GString lData = serialize();
    lData = GCALL_SERVER("query", "delete_query_type", lData);
    deserialize(lData);
}
//===============================================
