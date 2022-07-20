//===============================================
#ifndef _GSession_
#define _GSession_
//===============================================
#include "GObject.h"
//===============================================
class GSession : public GObject {
    Q_OBJECT

public:
    GSession(QObject* _parent = 0);
    ~GSession();
    QString serialize(const QString& _code = "session") const;
    void deserialize(const QString& _data, const QString& _code = "session");

protected:
    int m_userId;
};
//==============================================
#endif
//==============================================
