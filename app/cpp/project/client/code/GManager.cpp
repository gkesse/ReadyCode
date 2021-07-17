//===============================================
#include "GManager.h"
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
    mgr->app->sqlite_db_path = "database.dat";
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
    "select count(*) from users\n"
    "where username = '%1'\n"
    "").arg(username)).toInt();
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
    "insert into users (username, password)\n"
    "values ('%1', '%2')\n"
    "").arg(username, lPassword));
}
//===============================================
void GManager::updateUser(const QString& username, const QString& password) {
    QString lPassword = getPassword(username, password);
    GSQLite::Instance()->writeData(QString(""
    "update users\n"
    "set password = '%2'\n"
    "where username = '%1'\n"
    "").arg(username, lPassword));
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
