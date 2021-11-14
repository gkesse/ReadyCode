//===============================================
#ifndef _GSocketClient_
#define _GSocketClient_
//===============================================
#include "GSocketUi.h"
//===============================================
class GSocketClient : public GSocketUi {
public:
	GSocketClient();
	virtual ~GSocketClient();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
