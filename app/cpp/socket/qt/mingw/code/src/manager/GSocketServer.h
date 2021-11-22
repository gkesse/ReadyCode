//===============================================
#ifndef _GSocketServer_
#define _GSocketServer_
//===============================================
#include "GSocketUi.h"
//===============================================
class GSocketServer : public GSocketUi {
public:
    GSocketServer();
    ~GSocketServer();
    void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
