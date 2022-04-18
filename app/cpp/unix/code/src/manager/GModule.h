//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GObject.h"
//===============================================
class GCode;
class GSocket;
//===============================================
class GModule : public GObject {
public:
    GModule();
    GModule(const std::string& _req);
    virtual ~GModule();
    //
    virtual void onXmlInvalid(GSocket* _client);
    virtual void onReqInvalid(GSocket* _client);
    virtual void onModuleUnknown(GSocket* _client);
    virtual void onMethodUnknown(GSocket* _client);
    //
    void loadReq();
    void sendResponse(GSocket* _client);

protected:
    std::string m_xml;
    std::shared_ptr<GCode> m_req;
};
//==============================================
#endif
//==============================================
