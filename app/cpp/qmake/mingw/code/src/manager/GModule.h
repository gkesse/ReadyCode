//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GSession.h"
//===============================================
class GModule : public GSession {
    Q_OBJECT

public:
    GModule(QObject* _parent = 0);
    virtual ~GModule();
    //
    virtual QString serialize(const QString& _code = "request") const;
    virtual void deserialize(const QString& _data, const QString& _code = "request");
    virtual QString getModule() const;
    virtual QString getMethod() const;
    //
    virtual void onModuleNone(GSocket* _client);
    virtual void onMethodNone(GSocket* _client);
    virtual void onModuleUnknown(GSocket* _client);
    virtual void onMethodUnknown(GSocket* _client);

protected:
    QString m_module;
    QString m_method;
};
//==============================================
#endif
//==============================================
