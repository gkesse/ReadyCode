//===============================================
#include "GSearch.h"
#include "GCode.h"
//===============================================
GSearch::GSearch(const GString& _code)
: GManager(_code) {
    m_lastId = 0;
    m_dataCount = 0;
    m_dataSize = 0;
    m_dataOffset = 0;
    m_hasData = false;
    m_where = "where 1 = 1";
}
//===============================================
GSearch::~GSearch() {

}
//===============================================
GString GSearch::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "last_id", m_lastId);
    lDom.addData(_code, "data_count", m_dataCount);
    lDom.addData(_code, "data_size", m_dataSize);
    lDom.addData(_code, "data_offset", m_dataOffset);
    lDom.addData(_code, "has_data", m_hasData);
    return lDom.toString();
}
//===============================================
bool GSearch::deserialize(const GString& _data, const GString& _code) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_lastId = lDom.getData(_code, "last_id").toInt();
    m_dataCount = lDom.getData(_code, "data_count").toInt();
    m_dataSize = lDom.getData(_code, "data_size").toInt();
    m_dataOffset = lDom.getData(_code, "data_offset").toInt();
    m_hasData = lDom.getData(_code, "has_data").toBool();
    return true;
}
//===============================================
void GSearch::setSearch(const GSearch& _search) {
    m_lastId = _search.m_lastId;
    m_dataCount = _search.m_dataCount;
    m_dataSize = _search.m_dataSize;
    m_dataOffset = _search.m_dataOffset;
    m_hasData = _search.m_hasData;
}
//===============================================
