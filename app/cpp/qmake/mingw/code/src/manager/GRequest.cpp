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
    QString lDataOut = GSocket().callServer("req", "get_reques_list");
}
//===============================================
