//===============================================
#ifndef _GPocoRequestFactory_
#define _GPocoRequestFactory_
//===============================================
#include "GObject.h"
//===============================================
class GPocoRequestFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& _request);
};
//==============================================
#endif
//==============================================
