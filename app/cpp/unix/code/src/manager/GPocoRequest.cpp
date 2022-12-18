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
    GPoco lPoco;
    lPoco.onRequest(_request, _response);
}
//===============================================
