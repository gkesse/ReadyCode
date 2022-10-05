//===============================================
#include "GSearch.h"
#include "GCode.h"
//===============================================
GSearch::GSearch()
: GModule() {
    m_lastId = 0;
    m_dataCount = 0;
    m_dataSize = 0;
    m_dataOffset = 0;
    m_where = "where 1 = 1";
}
//===============================================
GSearch::~GSearch() {

}
//===============================================
GString GSearch::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "last_id", m_lastId);
    lDom.addData(_code, "data_count", m_dataCount);
    lDom.addData(_code, "data_size", m_dataSize);
    lDom.addData(_code, "data_offset", m_dataOffset);
    return lDom.toString();
}
//===============================================
bool GSearch::deserialize(const GString& _data, const GString& _code) {
    GModule::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_lastId = lDom.getData(_code, "last_id").toInt();
    m_dataCount = lDom.getData(_code, "data_count").toInt();
    m_dataSize = lDom.getData(_code, "data_size").toInt();
    m_dataOffset = lDom.getData(_code, "data_offset").toInt();
    return true;
}
//===============================================
