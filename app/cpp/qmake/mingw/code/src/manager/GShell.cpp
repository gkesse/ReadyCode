//===============================================
#include "GShell.h"
#include "GLog.h"
#include "GEnv.h"
#include "GFile.h"
#include "GDate.h"
//===============================================
GShell::GShell()
: GObject() {

}
//===============================================
GShell::~GShell() {

}
//===============================================
QString GShell::getTmpDir() const {
    return GEnv().getTmpDir();
}
//===============================================
QString GShell::getTmpInFilename() const {
    return GFile().getScriptInFilename();
}
//===============================================
QString GShell::getTmpOutFilename() const {
    return GFile().getScriptOutFilename();
}
//===============================================
void GShell::createDir(const QString& _dir) {
    if(_dir == "") return;
    QString lCommand = QString("if ! [ -d %1 ] ; then mkdir -p %1 ; fi").arg(_dir);
    runCommand(lCommand);
}
//===============================================
void GShell::tailFile(const QString& _file) {
    if(_file == "") return;
    QString lCommand = QString("if [ -e %1 ] ; then tail -f %1 ; fi").arg(_file);
    runCommand(lCommand);
}
//===============================================
void GShell::cleanDir(const QString& _dir) {
    if(_dir == "") return;
    QString lCommand = QString("if [ -d %1 ] ; then rm -rf %1/* ; fi").arg(_dir);
    runCommand(lCommand);
}
//===============================================
void GShell::runCommand(const QString& _command) {
    system(_command.toStdString().c_str());
}
//===============================================
QString GShell::runSystem(const QString& _command) {
    GLOGT(eGINF, _command);
    return runSystem(_command, getTmpDir(), getTmpInFilename(), getTmpOutFilename());
}
//===============================================
QString GShell::runSystem(const QString& _command, const QString& _tmpDir, const QString& _tmpInFile, const QString& _tmpOutFile) {
    createDir(_tmpDir);
    QString lFilenameIn = QString("%1/%2").arg(_tmpDir).arg(_tmpInFile);
    QString lFilenameOut = QString("%1/%2").arg(_tmpDir).arg(_tmpOutFile);
    GFile(lFilenameIn).setContent(_command);
    QString lCommand = QString(". %1 > %2").arg(lFilenameIn).arg(lFilenameOut);
    runCommand(lCommand);
    QString lData = GFile(lFilenameOut).getContent();
    return lData;
}
//===============================================
