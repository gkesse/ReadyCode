//===============================================
#ifndef _GAsioUi_
#define _GAsioUi_
//===============================================
#include "GInclude.h"
//===============================================
class GAsioUi {
public:
	GAsioUi();
	virtual ~GAsioUi();
	static GAsioUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
