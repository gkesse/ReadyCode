//===============================================
#include "GSQLiteTablesShow.h"
#include "GManager.h"
#include "GSQLite.h"
//===============================================
GSQLiteTablesShow::GSQLiteTablesShow(QObject* parent) :
GSQLiteUi(parent) {

}
//===============================================
GSQLiteTablesShow::~GSQLiteTablesShow() {

}
//===============================================
void GSQLiteTablesShow::run(int argc, char** argv) {
	QVector<QString> lDataMap = GSQLite::Instance()->readCol(""
			"select name from sqlite_master"
			"");
	for(int i = 0; i < lDataMap.size(); i++) {
		QString lData = lDataMap.at(i).toUpper();
		qDebug() << QString("[sqlite] %1").arg(lData);
	}
}
//===============================================
