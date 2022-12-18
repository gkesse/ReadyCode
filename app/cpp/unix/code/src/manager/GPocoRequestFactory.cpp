//===============================================
#include "GPocoRequestFactory.h"
#include "GPocoRequest.h"
#include "GPoco.h"
#include "GLog.h"
//===============================================
GPocoRequestFactory::GPocoRequestFactory(GPoco* _poco) {
    m_poco = _poco;
}
//===============================================
GPocoRequestFactory::~GPocoRequestFactory() {

}
//===============================================
Poco::Net::HTTPRequestHandler* GPocoRequestFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& _request) {
    GLOGT(eGFUN, "");
    return new GPocoRequest(m_poco);
}
//===============================================
