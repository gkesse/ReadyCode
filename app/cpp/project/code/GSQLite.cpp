//===============================================
#include "GSQLite.h"
#include "GManager.h"
//===============================================
GSQLite* GSQLite::m_instance = 0;
//===============================================
GSQLite::GSQLite() {
	open();
}
//===============================================
GSQLite::~GSQLite() {

}
//===============================================
GSQLite* GSQLite::Instance() {
	if(m_instance == 0) {
		m_instance = new GSQLite;
	}
	return m_instance;
}
//===============================================
void GSQLite::open() {
	sGApp* lApp = GManager::Instance()->getData()->app;
	if(QSqlDatabase::isDriverAvailable(lApp->sqlite_driver)) {
		QSqlDatabase lDb = QSqlDatabase::addDatabase(lApp->sqlite_driver);
		lDb.setDatabaseName(lApp->sqlite_db_path);
		if(!lDb.open()) {
			qDebug() << "[sqlite] erreur ouverture bdd : " << lDb.lastError();
		}
	}
	else {
		qDebug() << "[sqlite] erreur driver indisponible";
	}
}
//===============================================
bool GSQLite::writeData(const QString& sql) {
	QSqlQuery lQuery(sql);
	if(!lQuery.isActive()) {
		qDebug() << "[sqlite] erreur ecriture donnees";
		qDebug() << sql;
		return false;
	}
	return true;
}
//===============================================
QString GSQLite::readData(const QString& sql) {
	QSqlQuery lQuery(sql);
	if(!lQuery.isActive()) {
		qDebug() << "[sqlite] erreur lecture valeur";
	}
	QString lData = "";
	if(lQuery.first()) {
		lData = lQuery.value(0).toString();
	}
	return lData;
}
//===============================================
QVector<QVector<QString>> GSQLite::readMap(const QString& sql) {
	QSqlQuery lQuery(sql);
	if(!lQuery.isActive()) {
		qDebug() << "[sqlite] erreur lecture map";
	}
	QVector<QVector<QString>> lDataMap;
	int lColCount = lQuery.record().count();
    while (lQuery.next()) {
		QVector<QString> lDataRow;
    	for(int lCol = 0; lCol < lColCount; lCol++) {
    		QString lData = lQuery.value(lCol).toString();
    		lDataRow << lData;
    	}
    	lDataMap << lDataRow;
    }
	return lDataMap;
}
//===============================================
QStringList GSQLite::getFields(const QString& table) {
	QSqlDatabase lDb = QSqlDatabase::database();
	QSqlRecord lRecord = lDb.record(table);
	int lCount = lRecord.count();
	QStringList lFields;
	for(int i = 0; i < lCount; i++) {
		QString lField = lRecord.fieldName(i).toUpper();
		lFields << lField;
	}
	return lFields;
}
//===============================================
