//===============================================
#ifndef _GXmlRpcUi_
#define _GXmlRpcUi_
//===============================================
#include "GInclude.h"
#include "GXmlRpcM.h"
//===============================================
class GXmlRpcUi {
public:
	GXmlRpcUi();
	virtual ~GXmlRpcUi();
	static GXmlRpcUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
    static void onAdd(GXmlRpcM::pList _params, GXmlRpcM::pValue _value);
};
//==============================================
#endif
//==============================================
