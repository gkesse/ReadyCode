//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GObject.h"
//===============================================
class GServer : public GObject {
public:
    GServer();
    ~GServer();
    void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================