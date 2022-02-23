//===============================================
#include "GProcess.h"
#include "GTest.h"
#include "GPad.h"
//===============================================
GProcess::GProcess(QObject* _parent) :
GObject(_parent) {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
void GProcess::run(int _argc, char** _argv) {
	QString lKey = "default";
	if(_argc > 1) lKey = _argv[1];

	if(lKey == "default") {
		runTest(_argc, _argv);
	}
	else if(lKey == "pad") {
		runPad(_argc, _argv);
	}
	else {
		runTest(_argc, _argv);
	}
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
	GTest* lObj = new GTest;
	lObj->run(_argc, _argv);
	delete lObj;
}
//===============================================
void GProcess::runPad(int _argc, char** _argv) {
	QApplication lApp(_argc, _argv);
	GPad* lPad = new GPad;
	lPad->show();
	lApp.exec();
}
//===============================================
