//===============================================
#ifndef _GSocketClient_
#define _GSocketClient_
//===============================================
#include "GSocketUi.h"
//===============================================
class GSocketClient : public GSocketUi {
public:
    GSocketClient();
    ~GSocketClient();
    void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
