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
    virtual std::string serialize(const std::string& _code = "session") const;
    virtual void deserialize(const std::string& _data, const std::string& _code = "session");

protected:
    int m_userId;
};
//==============================================
#endif
//==============================================
