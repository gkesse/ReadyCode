//===============================================
#include "GQtUi.h"
//===============================================
GQtUi::GQtUi(QObject* parent) :
QObject(parent) {

}
//===============================================
GQtUi::~GQtUi() {

}
//===============================================
GQtUi* GQtUi::Create(const QString& key, QObject* parent) {
    if(key == "default") {return new GQtUi(parent);}
    return new GQtUi(parent);
}
//===============================================
void GQtUi::run(int argc, char** argv) {
    qDebug() << "[qt] aucun process n'a ete selectionne.";
    QProcess lProcess;
    lProcess.setProcessChannelMode(QProcess::MergedChannels);
    lProcess.start("sqlite3 --version");
    lProcess.waitForFinished(-1);
    QString lStdout = lProcess.readAllStandardOutput();
    qDebug() << lStdout;
    qDebug() << lProcess.error();
}
//===============================================
void GQtUi::onStart() {
	onEvent("start");
}
//===============================================
void GQtUi::onReady() {
	onEvent("ready");
}
//===============================================
void GQtUi::onReadyError() {
	onEvent("ready_error");
}
//===============================================
void GQtUi::onError(QProcess::ProcessError error) {
	onEvent("error");
}
//===============================================
void GQtUi::onEvent(const QString& text) {
	qDebug() << text << "...";
}
//===============================================
