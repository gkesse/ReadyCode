//===============================================
#ifndef _GPocoRequestFactory_
#define _GPocoRequestFactory_
//===============================================
#include "GObject.h"
//===============================================
class GPocoRequestFactory : public Poco::Net::HTTPRequestHandlerFactory {
protected:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& _request);
};
//==============================================
#endif
//==============================================
