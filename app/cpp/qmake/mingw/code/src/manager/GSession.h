//===============================================
#ifndef _GSession_
#define _GSession_
//===============================================
#include "GObject.h"
//===============================================
class GSession : public GObject {
public:
    GSession();
    ~GSession();
    QString serialize(const QString& _code = "session") const;
    void deserialize(const QString& _data, const QString& _code = "session");

protected:
    int m_userId;
};
//==============================================
#endif
//==============================================
