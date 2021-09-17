//===============================================
#include "GManager.h"
#include "GSQLite.h"
#include "GSQLiteFieldsShow.h"
//===============================================
GSQLiteFieldsShow::GSQLiteFieldsShow(QObject* parent) :
GSQLiteUi(parent) {

}
//===============================================
GSQLiteFieldsShow::~GSQLiteFieldsShow() {

}
//===============================================
void GSQLiteFieldsShow::run(int argc, char** argv) {
	QString lTable = "user_data";
	if(argc > 3) {lTable = argv[3];}
	lTable = lTable.toUpper();
	QStringList lDataMap = GManager::Instance()->getTableFields(lTable);
	for(int i = 0; i < lDataMap.size(); i++) {
		QString lData = lDataMap.at(i).toUpper();
		qDebug() << QString("[sqlite] %1 : %2")
				.arg(lTable).arg(lData);
	}
}
//===============================================
