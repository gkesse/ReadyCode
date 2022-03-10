//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GObject.h"
//===============================================
class GTest : public GObject {
public:
	GTest();
	~GTest();
	void run(int _argc, char** _argv);
	void runTest(int _argc, char** _argv);
	void runPath(int _argc, char** _argv);
	void runFormat(int _argc, char** _argv);
	void runXml(int _argc, char** _argv);
	std::string getPadItem(const std::string& _data) const;
};
//===============================================
#endif
//===============================================
