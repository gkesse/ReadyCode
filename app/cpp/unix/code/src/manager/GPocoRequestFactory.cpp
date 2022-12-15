//===============================================
#include "GPocoRequestFactory.h"
#include "GPocoRequest.h"
#include "GLog.h"
//===============================================
Poco::Net::HTTPRequestHandler* GPocoRequestFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& _request) {
    GLOGT(eGFUN, "");
    return new GPocoRequest;
}
//===============================================
