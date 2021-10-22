//===============================================
#ifndef _GAsioClient_
#define _GAsioClient_
//===============================================
#include "GAsioUi.h"
//===============================================
class GAsioClient : public GAsioUi {
public:
	GAsioClient();
	virtual ~GAsioClient();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
