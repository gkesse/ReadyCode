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
QString GManager::getMd5(const QString& data) {
	QString lData = QString(QCryptographicHash::hash(data.toLatin1(), QCryptographicHash::Md5).toHex());
	return lData;
}
//===============================================
QString GManager::getPassword(const QString& username, const QString& password) {
	QString lData = getMd5(QString("%1|%2").arg(username, password));
	return lData;
}
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
			"").arg(username, lPassword));
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
QStringList GManager::getTableFields(const QString& table) {
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
QStringList GManager::getDirFiles(const QString& path, const QStringList& filters) {
	QDirIterator lDirIt(path, filters, QDir::Files, QDirIterator::NoIteratorFlags);
	QStringList lFiles;
	while (lDirIt.hasNext()) {
		lFiles << lDirIt.next();
	}
	return lFiles;
}
//===============================================
bool GManager::runCmd(const QString& cmd) {
	int lAnswer = system(cmd.toStdString().c_str());
	bool lOk = (lAnswer == 0);
	return lOk;
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
void GManager::clearLayout(QLayout* layout) {
    if(layout) {
        while(layout->count() > 0) {
            QLayoutItem* lItem = layout->takeAt(0);
            QWidget* lWidget = lItem->widget();
            if(lWidget) delete lWidget;
            delete lItem;
        }
    }
}
//===============================================
void GManager::setPage(const QString& address)  {
    sGApp* lApp = GManager::Instance()->getData()->app;
    int lPageId = lApp->page_map->getPageId(address);
    if(lPageId == -1) {
        //setPage("home/error");
        //lApp->address_key->setContent(address);
        return;
    }
    GProUi* lPage = lApp->page_map->getPage(address);
    //lApp->address_new = address;
    if(lPage->loadPage() == 0) {
    	//lApp->address->setText(lApp->address_url);
        return;
    }
    lApp->page_map->setPage(address);
    //lApp->address->setText(address);
    //lApp->address_url = address;
    lApp->address_key->setContent(address);
    lApp->title_bar->setTitle(lApp->page_map->getTitle(address));
}
//===============================================
