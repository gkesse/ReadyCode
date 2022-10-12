//===============================================
#include "GSearch.h"
#include "GCode.h"
//===============================================
GSearch::GSearch()
: GManager() {
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
