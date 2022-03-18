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
    virtual void onModuleUnknown(GSocket* _client);
    virtual void onMethodUnknown(GSocket* _client);
    //
    void setRequest(const std::string& _req);
    void sendResponse(GSocket* _client);

protected:
    std::shared_ptr<GCode> m_req;
};
//==============================================
#endif
//==============================================
