//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GModule.h"
//===============================================
class GTest : public GManager {
public:
	GTest();
	~GTest();
	void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
};
//===============================================
#endif
//===============================================
