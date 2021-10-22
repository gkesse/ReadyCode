//===============================================
#ifndef _GAsioServer_
#define _GAsioServer_
//===============================================
#include "GAsioUi.h"
#include "GAsio.h"
//===============================================
class GAsioServer : public GAsioUi {
public:
	GAsioServer();
	virtual ~GAsioServer();
    void run(int argc, char** argv);
    static void onThread(GAsio::socket_ptr _socket);
};
//==============================================
#endif
//==============================================
