//===============================================
#include "GManager.h"
#include "GSQLite.h"
//===============================================
GManager* GManager::m_instance = 0;
//===============================================
GManager::GManager() {
	// manager
	mgr = new sGManager;
	// app
	mgr->app = new sGApp;
	mgr->app->app_name = "ReadyApp";
	mgr->app->sqlite_driver = "QSQLITE";
	mgr->app->sqlite_db_path = "data/sqlite/db/database.dat";
	mgr->app->sqlite_sql_path = "data/sqlite/sql";
	mgr->app->sqlite_sql_master = "data/sqlite/sql/master/master.sh";
	mgr->app->sqlite_sql_tmp = "data/sqlite/sql/tmp/tmp.txt";
	mgr->app->sqlite_table_name = "";
	mgr->app->on_event = false;
}
//===============================================
GManager::~GManager() {

}
//===============================================
GManager* GManager::Instance() {
	if(m_instance == 0) {
		m_instance = new GManager;
	}
	return m_instance;
}
//===============================================
sGManager* GManager::getData() {
	return mgr;
}
//===============================================
// data
//===============================================
void GManager::setData(QTextEdit* textEdit, const QVector<QString>& data) {
	textEdit->clear();
	for(int i = 0; i < data.size(); i++) {
		QString lData = data.at(i);
		textEdit->append(lData);
	}

}
//===============================================
void GManager::setData(QComboBox* comboBox, const QVector<QString>& data) {
	for(int i = 0; i < data.size(); i++) {
		QString lData = data.at(i);
		comboBox->addItem(lData);
	}

}
//===============================================
void GManager::setData2(QTextEdit* textEdit, const QVector<QString>& data) {
	textEdit->clear();
	for(int i = 0; i < data.size(); i++) {
		QString lData = data.at(i);
		textEdit->append(lData.toUpper());
	}

}
//===============================================
void GManager::setData2(QComboBox* comboBox, const QVector<QString>& data) {
	for(int i = 0; i < data.size(); i++) {
		QString lData = data.at(i);
		comboBox->addItem(lData.toUpper());
	}

}
//===============================================
// user
//===============================================
int GManager::countUser(const QString& username) {
	int lCount = GSQLite::Instance()->readData(QString(""
			"select count(*) from user_data\n"
			"where _username = '%1'\n"
			"").arg(username)).toInt();
	return lCount;
}
//===============================================
int GManager::countUser(const QString& username, const QString& password) {
	QString lPassword = getPassword(username, password);
	int lCount = GSQLite::Instance()->readData(QString(""
			"select count(*) from user_data\n"
			"where _username = '%1'\n"
			"and _password = '%2'\n"
			"").arg(username, lPassword)).toInt();
	return lCount;
}
//===============================================
void GManager::saveUser(const QString& username, const QString& password) {
	int lCount = countUser(username);
	if(lCount == 0) {
		insertUser(username, password);
	}
	else {
		updateUser(username, password);
	}
}
//===============================================
void GManager::insertUser(const QString& username, const QString& password) {
	QString lPassword = getPassword(username, password);
	GSQLite::Instance()->writeData(QString(""
			"insert into user_data (_username, _password)\n"
			"values ('%1', '%2')\n"
			"").arg(username).arg(lPassword));
}
//===============================================
void GManager::updateUser(const QString& username, const QString& password) {
	QString lPassword = getPassword(username, password);
	GSQLite::Instance()->writeData(QString(""
			"update user_data\n"
			"set _password = '%2'\n"
			"where _username = '%1'\n"
			"").arg(username, lPassword));
}
//===============================================
QString GManager::getPassword(const QString& username, const QString& password) {
	QString lData = getMd5(QString("%1|%2").arg(username, password));
	return lData;
}
//===============================================
// login
//===============================================
void GManager::saveLogin(const QString& username, const QString& login) {
	int lCount = countLogin(username);
	if(lCount == 0) {
		insertLogin(username, login);
	}
	else {
		updateLogin(username, login);
	}
}
//===============================================
int GManager::countLogin() {
	int lCount = GSQLite::Instance()->readData(QString(""
			"select count(*) from login_data\n"
			"where _login = '1'\n"
			"")).toInt();
	return lCount;
}
//===============================================
int GManager::countLogin(QString username) {
	int lCount = GSQLite::Instance()->readData(QString(""
			"select count(*) from login_data\n"
			"where _username = '%1'\n"
			"").arg(username)).toInt();
	return lCount;
}
//===============================================
void GManager::insertLogin(QString username, QString login) {
	GSQLite::Instance()->writeData(QString(""
			"insert into login_data (_username, _login)\n"
			"values ('%1', '%2')\n"
			"").arg(username).arg(login));
}
//===============================================
void GManager::updateLogin(QString username, QString login) {
	GSQLite::Instance()->writeData(QString(""
			"update login_data\n"
			"set _login = '%2'\n"
			"where _username = '%1'\n"
			"").arg(username).arg(login));
}
//===============================================
// file_id
//===============================================
int GManager::countFileId(const QString& fileId) {
	int lCount = GSQLite::Instance()->readData(QString(""
			"select count(*) from file_id_data\n"
			"where _file_id = %1"
			"").arg(fileId)).toInt();
	return lCount;
}
//===============================================
// sqlite
//===============================================
QVector<QString> GManager::getTables() {
	QVector<QString> lTables = GSQLite::Instance()->readCol(QString(""
			"select name from sqlite_master\n"
			"where type = 'table'\n"
			"order by name\n"
			""));
	return lTables;
}
//===============================================
QString GManager::getSchema(const QString& table) {
	QString lSchema = GSQLite::Instance()->readData(QString(""
			"select sql from sqlite_master\n"
			"where type = 'table'\n"
			"and name = '%1'\n"
			"").arg(table));
	return lSchema;
}
//===============================================
void GManager::deleteTable(const QString& table) {
	GSQLite::Instance()->writeData(QString(""
			"drop table %1\n"
			"").arg(table));
}
//===============================================
QStringList GManager::getFields(const QString& table) {
	return GSQLite::Instance()->getFields(table);
}
//===============================================
QVector<QVector<QString>> GManager::getTableData(const QString& table) {
	QString lSql = QString(""
			"select * from %1\n"
			"").arg(table);
	return GSQLite::Instance()->readMap(lSql);
}
//===============================================
// file
//===============================================
QStringList GManager::getDirFiles(const QString& path, const QStringList& filters) {
	QDirIterator lDirIt(path, filters, QDir::Files, QDirIterator::NoIteratorFlags);
	QStringList lFiles;
	while (lDirIt.hasNext()) {
		lFiles << lDirIt.next();
	}
	return lFiles;
}
//===============================================
QString GManager::readFile(const QString& path) {
	QFile lFile(path);
	QString lData = "";
	if (lFile.open(QIODevice::ReadOnly)) {
		lData = lFile.readAll();
	}
	return lData;
}
//===============================================
// message
//===============================================
void GManager::showMessage(QWidget* parent, const QString& title, const QString& text) {
	QMessageBox::information(parent, title, text);
}
//===============================================
void GManager::showWarning(QWidget* parent, const QString& title, const QString& text) {
	QMessageBox::warning(parent, title, text);
}
//===============================================
void GManager::showError(QWidget* parent, const QString& title, const QString& text) {
	QMessageBox::critical(parent, title, text);
}
//===============================================
int GManager::showQuestion(QWidget* parent, const QString& title, const QString& text, QMessageBox::StandardButtons buttons) {
	return QMessageBox::question(parent, title, text, buttons);
}
//===============================================
int GManager::confirm(QWidget* parent) {
	int lOk = showQuestion(parent, "SQLite | Confirmation",
			"Êtes-vous sûr de vouloir continuer ?");
	return lOk;
}
//===============================================
// divers
//===============================================
QString GManager::getMd5(const QString& data) {
	QString lData = QString(QCryptographicHash::hash(data.toLatin1(), QCryptographicHash::Md5).toHex());
	return lData;
}
//===============================================
bool GManager::runCmd(const QString& cmd) {
	int lAnswer = system(cmd.toStdString().c_str());
	bool lOk = (lAnswer == 0);
	return lOk;
}
//===============================================
