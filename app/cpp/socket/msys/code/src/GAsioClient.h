//===============================================
#ifndef _GAsioClient_
#define _GAsioClient_
//===============================================
#include "GAsioUi.h"
#include "GAsio.h"
//===============================================
class GAsioClient : public GAsioUi {
public:
	GAsioClient();
	virtual ~GAsioClient();
    void run(int argc, char** argv);
    static void onAsync(const GAsio::error_ptr& _errorcode);
};
//==============================================
#endif
//==============================================
