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
    m_params.reset(new GCode);
    m_params->createCode();
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
void GRequest::setId(int _id) {
    m_id = _id;
}
//===============================================
void GRequest::serialize() {
    m_params->addParam("id", QString("%1").arg(m_id));
    m_params->addParam("module", m_module);
    m_params->addParam("method", m_method);
    m_params->addParam("msg", m_msg);
}
//===============================================
void GRequest::getRequestList() {
    GSocket lClient;
    serialize();
    QString lDataOut = lClient.callServer("req", "get_req_list", m_params);
    GCode lReqCode(lDataOut);
    int lCount = lReqCode.countItem("req");
    GLOGT(eGMSG, QString("%1").arg(lCount));

    for(int i = 0; i < lCount; i++) {
        GRequest* lReq = new GRequest;
        lReq->m_module = lReqCode.getItem("req", "module", i);
        lReq->m_method = lReqCode.getItem("req", "method", i);
        lReq->m_msg = lReqCode.getItem("req", "msg", i, true);
        m_reqs.push_back(lReq);
    }
}
//===============================================
