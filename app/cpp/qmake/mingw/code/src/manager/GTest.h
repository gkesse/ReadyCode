//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GObject.h"
//===============================================
class GTest : public GObject {
	Q_OBJECT

public:
	GTest(QObject* _parent = 0);
	~GTest();
	void run(int _argc, char** _argv);
	void runTest(int _argc, char** _argv);
	void runLogin(int _argc, char** _argv);
};
//===============================================
#endif
//===============================================
