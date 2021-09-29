//===============================================
#ifndef _GSocketServer_
#define _GSocketServer_
//===============================================
#include "GSocketUi.h"
//===============================================
class GSocketServer : public GSocketUi {
	Q_OBJECT

public:
	GSocketServer(QObject* parent = 0);
	virtual ~GSocketServer();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
