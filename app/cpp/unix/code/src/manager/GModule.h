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
    virtual GString serialize(const GString& _code = "request") const;
    virtual void deserialize(const GString& _data, const GString& _code = "request");
    //
    virtual void onModuleNone(GSocket* _client);
    virtual void onMethodNone(GSocket* _client);
    virtual void onModuleUnknown(GSocket* _client);
    virtual void onMethodUnknown(GSocket* _client);

protected:
    GString m_module;
    GString m_method;
};
//==============================================
#endif
//==============================================
