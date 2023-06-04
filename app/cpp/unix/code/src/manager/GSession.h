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
    GSession();
    virtual ~GSession();
    virtual GString serialize(const GString& _code = "session");
    virtual void deserialize(const GString& _data, const GString& _code = "session");

protected:
    int m_userId;
};
//==============================================
#endif
//==============================================
