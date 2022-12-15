//===============================================
#ifndef _GPocoRequestFactory_
#define _GPocoRequestFactory_
//===============================================
#include "GObject.h"
//===============================================
class GPoco;
//===============================================
class GPocoRequestFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    GPocoRequestFactory(GPoco* _poco);
    ~GPocoRequestFactory();

protected:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& _request);

protected:
    GPoco* m_poco;
};
//==============================================
#endif
//==============================================
