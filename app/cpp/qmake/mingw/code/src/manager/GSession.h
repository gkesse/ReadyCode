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
    GString serialize(const GString& _code = "session") const;
    bool deserialize(const GString& _data, const GString& _code = "session");

protected:
    int m_userId;
};
//==============================================
#endif
//==============================================
