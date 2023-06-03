//===============================================
#ifndef _GSocketEcho_
#define _GSocketEcho_
//===============================================
#include "GSocket.h"
//===============================================
class GSocketEcho : public GSocket {
public:
    GSocketEcho();
    ~GSocketEcho();

protected:
    bool runThreadCB();
    bool runRequest();
};
//==============================================
#endif
//==============================================
