//===============================================
#include "GRequest.h"
#include "GLog.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GRequest::GRequest(QObject* _parent) : GObject(_parent) {

}
//===============================================
GRequest::~GRequest() {

}
//===============================================
void GRequest::getRequestList() {
    GSocket lClient;
    QString lDataOut = lClient.callServer("req", "get_req_list");
}
//===============================================
