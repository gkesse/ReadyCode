//===============================================
#ifndef _GXmlRpcServer_
#define _GXmlRpcServer_
//===============================================
#include "GXmlRpcUi.h"
#include "GXmlRpcM.h"
//===============================================
class GXmlRpcServer : public GXmlRpcUi {
public:
	GXmlRpcServer();
	virtual ~GXmlRpcServer();
    void run(int argc, char** argv);
    static void onAdd(GXmlRpcM::pList _params, GXmlRpcM::pValue _value);
};
//==============================================
#endif
//==============================================
