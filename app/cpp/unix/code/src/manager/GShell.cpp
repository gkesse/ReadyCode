//===============================================
#include "GShell.h"
#include "GLog.h"
#include "GEnv.h"
#include "GFile.h"
#include "GDate.h"
//===============================================
GShell::GShell() : GObject() {

}
//===============================================
GShell::~GShell() {

}
//===============================================
GString GShell::getTmpDir() const {
    return GEnv().getTmpDir();
}
//===============================================
GString GShell::getTmpInFilename() const {
    return GFile().getScriptInFilename();
}
//===============================================
GString GShell::getTmpOutFilename() const {
    return GFile().getScriptOutFilename();
}
//===============================================
void GShell::createDir(const GString& _dir) {
    GString lCommand = GFORMAT("if ! [ -d %s ] ; then mkdir -p %s ; fi", _dir.c_str(), _dir.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell::tailFile(const GString& _file) {
    GString lCommand = GFORMAT("if [ -e %s ] ; then tail -f %s ; fi", _file.c_str(), _file.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell::cleanDir(const GString& _dir) {
    GString lCommand = GFORMAT("if [ -d %s ] ; then rm -rf %s/* ; fi", _dir.c_str(), _dir.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell::runCommand(const GString& _command) {
    if(_command == "") return;
    GLOGT(eGOFF, "%s", _command.c_str());
    system(_command.c_str());
}
//===============================================
GString GShell::runSystem(const GString& _command) {
    GLOGT(eGINF, "%s", _command.c_str());
    return runSystem(_command, getTmpDir(), getTmpInFilename(), getTmpOutFilename());
}
//===============================================
GString GShell::runSystem(const GString& _command, const GString& _tmpDir, const GString& _tmpInFile, const GString& _tmpOutFile) {
    createDir(_tmpDir);
    GString lFilenameIn = GFORMAT("%s/%s", _tmpDir.c_str(), _tmpInFile.c_str());
    GString lFilenameOut = GFORMAT("%s/%s", _tmpDir.c_str(), _tmpOutFile.c_str());
    GFile(lFilenameIn).setContent(_command);
    GString lCommand = GFORMAT(". %s > %s", lFilenameIn.c_str(), lFilenameOut.c_str());
    runCommand(lCommand);
    GString lData = GFile(lFilenameOut).getContent();
    return lData;
}
//===============================================
