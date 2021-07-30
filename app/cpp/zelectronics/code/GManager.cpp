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
