//===============================================
#ifndef _GSocketServer_
#define _GSocketServer_
//===============================================
#include "GSocketUi.h"
//===============================================
class GSocketServer : public GSocketUi {
public:
	GSocketServer();
	virtual ~GSocketServer();
	void run(int argc, char** argv);

private:
	const char APRESSMESSAGE[] = ""
			"APRESS - For Professionals, By Professionals!\n";
};
//==============================================
#endif
//==============================================
