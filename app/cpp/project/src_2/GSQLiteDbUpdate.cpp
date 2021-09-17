//===============================================
#include "GSQLiteDbUpdate.h"
#include "GManager.h"
#include "GSQLite.h"
//===============================================
GSQLiteDbUpdate::GSQLiteDbUpdate(QObject* parent) :
GSQLiteUi(parent) {

}
//===============================================
GSQLiteDbUpdate::~GSQLiteDbUpdate() {

}
//===============================================
void GSQLiteDbUpdate::run(int argc, char** argv) {
	sGApp* lApp = GManager::Instance()->getData()->app;
	QStringList lFilters; lFilters << "*.sh";
	QStringList lFiles = GManager::Instance()->getDirFiles(lApp->sqlite_sql_path, lFilters);
	bool lValid = true;
	for(int i = 0; i < lFiles.size(); i++) {
		QString lFile = lFiles.at(i);
		QString lCmd = QString("bash %1")
						.arg(lFile);
		lValid &= GManager::Instance()->runCmd(lCmd);
	}
	if(lValid) {
		qDebug() << "[sqlite] La mise a jour a reussi.";
	}
}
//===============================================
