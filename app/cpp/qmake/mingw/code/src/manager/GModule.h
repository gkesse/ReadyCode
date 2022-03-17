//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GObject.h"
//===============================================
class GRequest;
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
    virtual void onModuleUnknown(const QString& _req, GSocket* _client);
    virtual void onMethodUnknown(const QString& _req, GSocket* _client);
    //
    void setRequest(const QString& _req);
    void sendResponse(GSocket* _client);

protected:
    QSharedPointer<GRequest> m_req;
};
//==============================================
#endif
//==============================================
