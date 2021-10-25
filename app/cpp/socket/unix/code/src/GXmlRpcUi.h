//===============================================
#ifndef _GXmlRpcUi_
#define _GXmlRpcUi_
//===============================================
#include "GInclude.h"
//===============================================
class GXmlRpcUi {
public:
	GXmlRpcUi();
	virtual ~GXmlRpcUi();
	static GXmlRpcUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
