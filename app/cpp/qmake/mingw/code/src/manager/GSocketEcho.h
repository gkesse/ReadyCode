//===============================================
#ifndef _GSocketEcho_
#define _GSocketEcho_
//===============================================
#include "GSocket.h"
//===============================================
class GSocketEcho : public GSocket {
public:
    GSocketEcho(const GString& _code = "socket_echo");
    ~GSocketEcho();

protected:
    bool onCallServer();
};
//==============================================
#endif
//==============================================
