//===============================================
#include "GFont.h"
#include "GProcess.h"
#include "GStyle2.h"
#include "GTest.h"
#include "GPadMdi.h"
#include "GLog.h"
#include "GWindowUi.h"
//===============================================
GProcess::GProcess()
: GObject() {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
void GProcess::run(int _argc, char** _argv) {
	QString lKey = "";
	if(_argc > 1) lKey = _argv[1];
	//===============================================
	// test
	//===============================================
    if(lKey == "test") {
        runTest(_argc, _argv);
    }
    //===============================================
    // pad
    //===============================================
    else if(lKey == "pad/mdi") {
        runPadMdi(_argc, _argv);
    }
    else if(lKey == "mainpad") {
        runMainPad(_argc, _argv);
    }
    //===============================================
	// end
    //===============================================
	else {
		runDefault(_argc, _argv);
	}
}
//===============================================
void GProcess::runDefault(int _argc, char** _argv) {
    GObject::runDefault(_argc, _argv);
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GTest lTest;
    lTest.run(_argc, _argv);
}
//===============================================
void GProcess::runPadMdi(int _argc, char** _argv) {
    QApplication lApp(_argc, _argv);
    if(!GFONT_LOAD()) return;
    if(!GSTYLE_LOAD()) return;
    GPadMdi* lPadMdi = new GPadMdi;
    lPadMdi->showMaximized();
    lApp.exec();
}
//===============================================
void GProcess::runMainPad(int _argc, char** _argv) {
    QApplication lApp(_argc, _argv);
    if(!GFONT_LOAD()) return;
    if(!GSTYLE_LOAD()) return;
    GWindowUi* lWindow = new GWindowUi;
    lWindow->show();
    lApp.exec();
}
//===============================================
