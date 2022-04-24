//===============================================
#include "GRequest.h"
#include "GLog.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GRequest::GRequest(QObject* _parent) : GObject(_parent) {
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
    GCode lReqs(lDataOut);
    int lCount = lReqs.countItem("req");
    GLOGT(eGMSG, QString("%1").arg(lCount));
    for(int i = 0; i < lCount; i++) {

    }
}
//===============================================
