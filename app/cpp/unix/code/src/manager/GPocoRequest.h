//===============================================
#ifndef _GPocoRequest_
#define _GPocoRequest_
//===============================================
#include "GObject.h"
//===============================================
class GPocoRequest : public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
};
//==============================================
#endif
//==============================================
