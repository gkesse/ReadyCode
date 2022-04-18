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
    virtual ~GModule();
    //
    virtual void onXmlInvalid(GSocket* _client);
    virtual void onReqInvalid(GSocket* _client);
    virtual void onModuleUnknown(GSocket* _client);
    virtual void onMethodUnknown(GSocket* _client);
    //
    void sendResponse(GSocket* _client);
};
//==============================================
#endif
//==============================================
