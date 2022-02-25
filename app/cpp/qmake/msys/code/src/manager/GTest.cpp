//===============================================
#include "GTest.h"
#include "GPath.h"
//===============================================
GTest::GTest(QObject* _parent) :
GObject(_parent) {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
	QString lKey = "default";
	if(_argc > 2) lKey = _argv[2];

	if(lKey == "default") {
		runTest(_argc, _argv);
	}
	else if(lKey == "login") {
		runLogin(_argc, _argv);
	}
	else {
		runTest(_argc, _argv);
	}
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
	QString lPath = GRES("xml", "app.xml");
	qDebug() << lPath;
}
//===============================================
void GTest::runLogin(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
}
//===============================================
