//===============================================
#include "GTest.h"
#include "GPath.h"
#include "GMySQL.h"
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
	else if(lKey == "path") {
		runPath(_argc, _argv);
	}
	else if(lKey == "mysql") {
		runMysql(_argc, _argv);
	}
	else {
		runTest(_argc, _argv);
	}
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
	printf("\n### %s\n\n", __FUNCTION__);
}
//===============================================
void GTest::runPath(int _argc, char** _argv) {
	printf("\n### %s\n\n", __FUNCTION__);
	QString lPath = GRES("xml", "app.xml");
	printf("=> %s\n", lPath.toStdString().c_str());
}
//===============================================
void GTest::runMysql(int _argc, char** _argv) {
	printf("\n### %s\n\n", __FUNCTION__);
	QSharedPointer<GMySQL> lMysql(new GMySQL);

	printf("\n### readData\n");
	QString lData = lMysql->readData("show databases");
	printf("=> %s\n", lData.toStdString().c_str());

	printf("\n### readCol\n");
	QVector<QString> lDataCol = lMysql->readCol("select user, host from mysql.user");
	for(int i = 0; i < lDataCol.size(); i++) {
		QString lValue = lDataCol.at(i);
		printf("=> %s\n", lValue.toStdString().c_str());
	}
}
//===============================================
