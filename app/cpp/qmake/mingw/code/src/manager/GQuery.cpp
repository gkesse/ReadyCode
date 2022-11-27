//===============================================
#include "GQuery.h"
#include "GCode.h"
#include "GLog.h"
#include "GBase64.h"
#include "GClient.h"
//===============================================
GQuery::GQuery(const GString& _code)
: GSearch(_code) {

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
    lDom.addData(_code, "emission", m_emission, true);
    lDom.addData(_code, "reception", m_reception, true);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
bool GQuery::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_emission = lDom.getData(_code, "emission");
    m_reception = lDom.getData(_code, "reception");
    return true;
}
//===============================================
void GQuery::setEmission(const GString& _emission) {
    m_emission = _emission.toBase64();
}
//===============================================
void GQuery::setReception(const GString& _reception) {
    m_reception = _reception.toBase64();
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
