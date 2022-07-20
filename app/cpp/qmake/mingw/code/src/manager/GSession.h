//===============================================
#ifndef _GSession_
#define _GSession_
//===============================================
#include "GObject.h"
//===============================================
class GCode;
class GSocket;
//===============================================
class GSession : public GObject {
    Q_OBJECT

public:
    GSession(QObject* _parent = 0);
    virtual ~GSession();
    virtual QString serialize(const QString& _code = "session") const;
    virtual void deserialize(const QString& _data, const QString& _code = "session");

protected:
    int m_userId;
};
//==============================================
#endif
//==============================================
