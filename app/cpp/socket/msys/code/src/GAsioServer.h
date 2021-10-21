//===============================================
#ifndef _GAsioServer_
#define _GAsioServer_
//===============================================
#include "GAsioUi.h"
//===============================================
class GAsioServer : public GAsioUi {
public:
	GAsioServer();
	virtual ~GAsioServer();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
