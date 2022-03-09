//===============================================
#include "GProcess.h"
#include "GTest.h"
//===============================================
GProcess::GProcess() : GObject() {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
void GProcess::run(int _argc, char** _argv) {
	std::string lKey = "default";
	if(_argc > 1) lKey = _argv[1];

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
void GProcess::runTest(int _argc, char** _argv) {
	std::shared_ptr<GTest> lObj(new GTest);
	lObj->run(_argc, _argv);
}
//===============================================
