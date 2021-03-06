//===============================================
#include "GProcess.h"
#include "GTest.h"
#include "GPadUi.h"
//===============================================
GProcess::GProcess(QObject* _parent) : GObject(_parent) {

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
	// test
    else if(lKey == "test") {
        runTest(_argc, _argv);
    }
	// pad
    else if(lKey == "pad") {
        runPad(_argc, _argv);
    }
	// end
	else {
		runDefault(_argc, _argv);
	}
}
//===============================================
void GProcess::runDefault(int _argc, char** _argv) {
    GTest lTest;
    lTest.run(_argc, _argv);
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GTest lTest;
    lTest.run(_argc, _argv);
}
//===============================================
void GProcess::runPad(int _argc, char** _argv) {
	QApplication lApp(_argc, _argv);
	GPadUi* lPad = new GPadUi;
	lPad->show();
	lApp.exec();
}
//===============================================
