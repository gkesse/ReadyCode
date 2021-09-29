//===============================================
#ifndef _GSocketClient_
#define _GSocketClient_
//===============================================
#include "GSocketUi.h"
//===============================================
class GSocketClient : public GSocketUi {
	Q_OBJECT

public:
	GSocketClient(QObject* parent = 0);
	virtual ~GSocketClient();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
