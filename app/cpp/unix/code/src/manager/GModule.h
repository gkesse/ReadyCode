//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GObject.h"
//===============================================
class GXml;
class GSocket;
//===============================================
class GModule : public GObject {
public:
    GModule();
    GModule(const std::string& _req);
    virtual ~GModule();
    //
    virtual void onModuleUnknown(const std::string& _req, GSocket* _client);
    virtual void onMethodUnknown(const std::string& _req, GSocket* _client);
    //
    void setRequest(const std::string& _req);
    std::string getModule();
    std::string getMethod();

protected:
    std::shared_ptr<GXml> m_req;
};
//==============================================
#endif
//==============================================
