//===============================================
#include "GRequest.h"
#include "GLog.h"
//===============================================
GRequest::GRequest(QObject* _parent) : GXml(_parent) {

}
//===============================================
GRequest::~GRequest() {

}
//===============================================
GRequest& GRequest::createRequest(const QString& _module, const QString& _method) {
    if(GLOGI->hasError()) return *this;
    createDoc("1.0", "rdv");
    createNodePath("/rdv/module", _module);
    createNodePath("/rdv/method", _method);
    return *this;
}
//===============================================
