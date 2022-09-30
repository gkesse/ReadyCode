//===============================================
#include "GShell2.h"
#include "GLog.h"
#include "GEnv.h"
#include "GFile2.h"
#include "GDate.h"
//===============================================
GShell2::GShell2()
: GObject2() {

}
//===============================================
GShell2::~GShell2() {

}
//===============================================
GString GShell2::getTmpDir() const {
    return GEnv().getTmpDir();
}
//===============================================
GString GShell2::getTmpInFilename() const {
    return GFile2().getScriptInFilename();
}
//===============================================
GString GShell2::getTmpOutFilename() const {
    return GFile2().getScriptOutFilename();
}
//===============================================
void GShell2::createDir(const GString& _dir) {
    GString lCommand = GFORMAT("if ! [ -d %s ] ; then mkdir -p %s ; fi", _dir.c_str(), _dir.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell2::tailFile(const GString& _file) {
    GString lCommand = GFORMAT("if [ -e %s ] ; then tail -f %s ; fi", _file.c_str(), _file.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell2::cleanDir(const GString& _dir) {
    GString lCommand = GFORMAT("if [ -d %s ] ; then rm -rf %s/* ; fi", _dir.c_str(), _dir.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell2::runCommand(const GString& _command) {
    if(_command == "") return;
    GLOGT(eGOFF, "%s", _command.c_str());
    system(_command.c_str());
}
//===============================================
GString GShell2::runSystem(const GString& _command) {
    GLOGT(eGINF, "%s", _command.c_str());
    return runSystem(_command, getTmpDir(), getTmpInFilename(), getTmpOutFilename());
}
//===============================================
GString GShell2::runSystem(const GString& _command, const GString& _tmpDir, const GString& _tmpInFile, const GString& _tmpOutFile) {
    createDir(_tmpDir);
    GString lFilenameIn = GFORMAT("%s/%s", _tmpDir.c_str(), _tmpInFile.c_str());
    GString lFilenameOut = GFORMAT("%s/%s", _tmpDir.c_str(), _tmpOutFile.c_str());
    GFile2(lFilenameIn).setContent(_command);
    GString lCommand = GFORMAT(". %s > %s", lFilenameIn.c_str(), lFilenameOut.c_str());
    runCommand(lCommand);
    GString lData = GFile2(lFilenameOut).getContent();
    return lData;
}
//===============================================
