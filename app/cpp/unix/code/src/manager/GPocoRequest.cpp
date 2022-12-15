//===============================================
#include "GPocoRequest.h"
#include "GPoco.h"
//===============================================
GPocoRequest::GPocoRequest(GPoco* _poco) {
    m_poco = _poco;
}
//===============================================
GPocoRequest::~GPocoRequest() {

}
//===============================================
void GPocoRequest::handleRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    m_poco->onRequest(_request, _response);
}
//===============================================
