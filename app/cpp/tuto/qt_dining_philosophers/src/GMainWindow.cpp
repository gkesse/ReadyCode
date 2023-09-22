//===============================================
#include "GMainWindow.h"
#include "ui_GMainWindow.h"
//===============================================
#include "GDinner.h"
//===============================================
GMainWindow::GMainWindow(QWidget* _parent)
: QMainWindow(_parent)
, ui(new Ui::GMainWindow) {
    ui->setupUi(this);
    m_dinner = 0;
}
//===============================================
GMainWindow::~GMainWindow() {

}
//===============================================
void GMainWindow::init() {
    setWindowTitle(QCoreApplication::applicationName());
    m_dinner = new GDinner(this);
    m_dinner->init();
    connect(this, &GMainWindow::emitStart, m_dinner, &GDinner::onStart);
    connect(this, &GMainWindow::emitStop, m_dinner, &GDinner::onStop);
}
//===============================================
void GMainWindow::on_actionAboutQt_triggered(bool checked) {
	QMessageBox::aboutQt(this, tr("À propos de Qt"));
}
//===============================================
void GMainWindow::on_actionClose_triggered(bool checked) {
	close();
}
//===============================================
void GMainWindow::on_actionSettings_triggered(bool checked) {

}
//===============================================
void GMainWindow::on_actionStart_triggered(bool checked) {
	emit emitStart();
}
//===============================================
void GMainWindow::on_actionStop_triggered(bool checked) {
	emit emitStop();
}
//===============================================
