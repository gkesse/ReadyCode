//===============================================
#ifndef _GXmlRpcClient_
#define _GXmlRpcClient_
//===============================================
#include "GXmlRpcUi.h"
//===============================================
class GXmlRpcClient : public GXmlRpcUi {
public:
	GXmlRpcClient();
	virtual ~GXmlRpcClient();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
