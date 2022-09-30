//===============================================
#include "GSearch.h"
#include "GLog.h"
#include "GCode.h"
#include "GMySQL.h"
#include "GSocket.h"
#include "GString.h"
#include "GMd5.h"
#include "GDefine.h"
//===============================================
GSearch::GSearch() : GModule() {
    m_lastId = 0;
    m_dataCount = 0;
    m_dataSize = 0;
    m_dataOffset = 0;
    m_where = " where 1 ";
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
    return lDom.toStringData();
}
//===============================================
void GSearch::deserialize(const GString& _data, const GString& _code) {
    GModule::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_lastId = GString(lDom.getItem(_code, "last_id")).toInt();
    m_dataCount = GString(lDom.getItem(_code, "data_count")).toInt();
    m_dataSize = GString(lDom.getItem(_code, "data_size")).toInt();
    m_dataOffset = GString(lDom.getItem(_code, "data_offset")).toInt();
}
//===============================================
