//===============================================
#include "GStyle.h"
#include "GFont.h"
#include "GProcess.h"
#include "GTest.h"
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
	GString lKey;
	if(_argc > 1) lKey = _argv[1];
	if(lKey == "test") {
        runTest(_argc, _argv);
    }
    else if(lKey == "pad") {
        runPad(_argc, _argv);
    }
	else {
		runDefault(_argc, _argv);
	}
}
//===============================================
void GProcess::runDefault(int _argc, char** _argv) {
    GLOGT(eGFUN, "Le process est inconnu.");
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GTest lTest;
    lTest.run(_argc, _argv);
}
//===============================================
void GProcess::runPad(int _argc, char** _argv) {
    QApplication lApp(_argc, _argv);
    if(!GFONT_LOAD()) return;
    if(!GSTYLE_LOAD()) return;
    GWindowUi* lWindow = new GWindowUi;
    lWindow->show();
    lApp.exec();
}
//===============================================
