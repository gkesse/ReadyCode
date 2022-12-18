//===============================================
#include "GPocoRequest.h"
#include "GPoco.h"
#include "GLog.h"
//===============================================
GPocoRequest::GPocoRequest(GPoco* _poco) {
    m_poco = _poco;
}
//===============================================
GPocoRequest::~GPocoRequest() {

}
//===============================================
void GPocoRequest::handleRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.onRequest(_request, _response);
}
//===============================================
