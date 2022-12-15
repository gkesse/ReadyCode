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
public:
    GSession(const GString& _code = "session");
    virtual ~GSession();
    virtual GString serialize(const GString& _code = "session") const;
    virtual bool deserialize(const GString& _data, const GString& _code = "session");

protected:
    int m_userId;
};
//==============================================
#endif
//==============================================
