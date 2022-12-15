//===============================================
#include "GRequest.h"
#include "GLog.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GRequest::GRequest(QObject* _parent)
: GModule(_parent) {
    m_id = 0;
    m_msg = "";
    m_dataOffset = 0;
    m_dataSize = 0;
    m_dataCount = 0;
}
//===============================================
GRequest::~GRequest() {

}
//===============================================
QString GRequest::serialize(const QString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "data_count", m_dataCount);
    lDom.addData(_code, "data_offset", m_dataOffset);
    lDom.addData(_code, "data_size", m_dataSize);
    return lDom.toStringData();
}
//===============================================
void GRequest::deserialize(const QString& _data, const QString& _code) {
    GModule::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getItem(_code, "id").toInt();
    m_msg = _data;
    m_dataOffset = lDom.getItem(_code, "data_offset").toInt();
    m_dataSize = lDom.getItem(_code, "data_size").toInt();
}
//===============================================
int GRequest::getId() const {
    return m_id;
}
//===============================================
QString GRequest::getMethod() const {
    return m_method;
}
//===============================================
QString GRequest::getModule() const {
    return m_module;
}
//===============================================
QString GRequest::getMsg() const {
    return m_msg;
}
//===============================================
void GRequest::setDataOffset(int _dataOffset) {
    m_dataOffset = _dataOffset;
}
//===============================================
void GRequest::setDataSize(int _dataSize) {
    m_dataSize = _dataSize;
}
//===============================================
void GRequest::getRequestList() {
    GSocket lClient;
    QString lParams = serialize();
    QString lDataOut = lClient.callServer("req", "get_req_list", lParams);
    GERROR_LOAD(eGERR, lDataOut);
    deserialize(lDataOut);
}
//===============================================
