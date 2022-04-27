//===============================================
#include "GRequest.h"
#include "GLog.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GRequest::GRequest(QObject* _parent) : GObject(_parent) {
    m_id = 0;
    m_module = "";
    m_method = "";
    m_msg = "";
    m_dataOffset = 0;
    m_dataSize = 0;
}
//===============================================
GRequest::~GRequest() {
    clearReqs();
}
//===============================================
void GRequest::clearReqs() {
    if(m_reqs.isEmpty()) return;
    for(int i = 0; i < m_reqs.size(); i++) {
        GRequest* lReq = m_reqs.at(i);
        delete lReq;
    }
    m_reqs.clear();
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
QVector<GRequest*>& GRequest::getReqs() {
    return m_reqs;
}
//===============================================
QVector<QString>& GRequest::getHeaders() {
    return m_headers;
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
QString GRequest::serialize() const {
    GCode lParams;
    lParams.createCode();
    lParams.addParam("id", m_id);
    lParams.addParam("module", m_module);
    lParams.addParam("method", m_method);
    lParams.addParam("msg", m_msg);
    lParams.addParam("data_offset", m_dataOffset);
    lParams.addParam("data_size", m_dataSize);
    return lParams.toStringCode("params");
}
//===============================================
void GRequest::deserializeMap(const QString& _data) {
    GCode lReqCode(_data);
    //
    int lCountHeader = lReqCode.countItem("req/header");
    for(int i = 0; i < lCountHeader; i++) {
        QString lHeader = lReqCode.getItem("req/header", "header", i);
        m_headers.push_back(lHeader);
    }
    //
    int lCountData = lReqCode.countItem("req");
    for(int i = 0; i < lCountData; i++) {
        GRequest* lReq = new GRequest;
        lReq->m_id = lReqCode.getItem("req", "id", i).toInt();
        lReq->m_module = lReqCode.getItem("req", "module", i);
        lReq->m_method = lReqCode.getItem("req", "method", i);
        lReq->m_msg = lReqCode.getItem("req", "msg", i, true);
        m_reqs.push_back(lReq);
    }
}
//===============================================
void GRequest::getRequestList() {
    GSocket lClient;
    QString lParams = serialize();
    QString lDataOut = lClient.callServer("req", "get_req_list", lParams);
    deserializeMap(lDataOut);
}
//===============================================
