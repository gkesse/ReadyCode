//===============================================
#ifndef _GPocoRequest_
#define _GPocoRequest_
//===============================================
#include "GObject.h"
//===============================================
class GPoco;
//===============================================
class GPocoRequest : public Poco::Net::HTTPRequestHandler {
public:
    GPocoRequest(GPoco* _poco);
    ~GPocoRequest();

protected:
    void handleRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

protected:
    GPoco* m_poco;
    GLog m_logs;
};
//==============================================
#endif
//==============================================
