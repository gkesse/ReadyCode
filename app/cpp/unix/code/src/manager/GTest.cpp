//===============================================
#include "GTest.h"
#include "GPath.h"
//===============================================
GTest::GTest() {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
	std::string lKey = "default";
	if(_argc > 2) lKey = _argv[2];

	if(lKey == "default") {
		runTest(_argc, _argv);
	}
	else if(lKey == "test") {
		runTest(_argc, _argv);
	}
	else {
		runTest(_argc, _argv);
	}
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
	std::string lPath = GRES("xml", "app.xml");
	printf("%s\n", lPath.c_str());
}
//===============================================
