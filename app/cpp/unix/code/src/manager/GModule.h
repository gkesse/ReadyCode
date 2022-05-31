//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GSession.h"
//===============================================
class GCode;
class GSocket;
//===============================================
class GModule : public GSession {
public:
    GModule();
    virtual ~GModule();
    virtual std::string serialize(const std::string& _code = "request") const;
    virtual void deserialize(const std::string& _data, const std::string& _code = "request");
    //
    virtual void onXmlInvalid(GSocket* _client);
    virtual void onReqInvalid(GSocket* _client);
    virtual void onModuleUnknown(GSocket* _client);
    virtual void onMethodUnknown(GSocket* _client);
    //
    void sendResponse(GSocket* _client);

protected:
    std::string m_module;
    std::string m_method;
};
//==============================================
#endif
//==============================================
