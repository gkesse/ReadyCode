//===============================================
#include "GSearch.h"
#include "GCode.h"
//===============================================
GSearch::GSearch(const GString& _codeName)
: GManager(_codeName) {
    m_lastId = 0;
    m_dataCount = 0;
    m_dataSize = 10;
    m_dataOffset = 0;
    m_hasData = false;
}
//===============================================
GSearch::~GSearch() {

}
//===============================================
GString GSearch::serialize() const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(m_codeName, "last_id", m_lastId);
    lDom.addData(m_codeName, "data_count", m_dataCount);
    lDom.addData(m_codeName, "data_size", m_dataSize);
    lDom.addData(m_codeName, "data_offset", m_dataOffset);
    lDom.addData(m_codeName, "has_data", m_hasData);
    return lDom.toString();
}
//===============================================
bool GSearch::deserialize(const GString& _data) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_lastId = lDom.getData(m_codeName, "last_id").toInt();
    m_dataCount = lDom.getData(m_codeName, "data_count").toInt();
    m_dataSize = lDom.getData(m_codeName, "data_size").toInt();
    m_dataOffset = lDom.getData(m_codeName, "data_offset").toInt();
    m_hasData = lDom.getData(m_codeName, "has_data").toBool();
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
bool GSearch::hasData() const {
    return m_hasData;
}
//===============================================
void GSearch::onNextData() {}
//===============================================
