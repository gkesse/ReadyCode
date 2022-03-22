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
    Q_OBJECT

public:
    GModule(QObject* _parent = 0);
    GModule(const QString& _req, QObject* _parent = 0);
    virtual ~GModule();
    //
    virtual void onModuleUnknown(GSocket* _client);
    virtual void onMethodUnknown(GSocket* _client);
    //
    void setRequest(const QString& _req);
    void sendResponse(GSocket* _client);

protected:
    QSharedPointer<GCode> m_req;
};
//==============================================
#endif
//==============================================
