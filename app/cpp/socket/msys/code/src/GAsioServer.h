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
    static void onThread(boost::shared_ptr<boost::asio::ip::tcp::socket> _socket);
};
//==============================================
#endif
//==============================================
