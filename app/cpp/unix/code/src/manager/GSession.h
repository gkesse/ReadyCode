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
    virtual GString serialize() const;
    virtual bool deserialize(const GString& _data);

protected:
    int m_userId;
};
//==============================================
#endif
//==============================================
