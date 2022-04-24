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
}
//===============================================
GRequest::~GRequest() {

}
//===============================================
void GRequest::serialize() {

}
//===============================================
void GRequest::getRequestList() {
    GSocket lClient;
    QString lDataOut = lClient.callServer("req", "get_req_list");
    GCode lReqCode(lDataOut);
    int lCount = lReqCode.countItem("req");
    GLOGT(eGMSG, QString("%1").arg(lCount));

    for(int i = 0; i < lCount; i++) {
        m_module = lReqCode.getItem("req", "module", i);
        m_method = lReqCode.getItem("req", "method", i);
        m_msg = lReqCode.getItem("req", "msg", i, true);
        m_reqs.push_back(*this);
    }
}
//===============================================
