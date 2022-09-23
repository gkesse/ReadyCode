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
GString2 GShell2::getTmpDir() const {
    return GEnv().getTmpDir();
}
//===============================================
GString2 GShell2::getTmpInFilename() const {
    return GFile2().getScriptInFilename();
}
//===============================================
GString2 GShell2::getTmpOutFilename() const {
    return GFile2().getScriptOutFilename();
}
//===============================================
void GShell2::createDir(const GString2& _dir) {
    GString2 lCommand = sformat("if ! [ -d %s ] ; then mkdir -p %s ; fi", _dir.c_str(), _dir.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell2::tailFile(const GString2& _file) {
    GString2 lCommand = sformat("if [ -e %s ] ; then tail -f %s ; fi", _file.c_str(), _file.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell2::cleanDir(const GString2& _dir) {
    GString2 lCommand = sformat("if [ -d %s ] ; then rm -rf %s/* ; fi", _dir.c_str(), _dir.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell2::runCommand(const GString2& _command) {
    if(_command == "") return;
    GLOGT(eGOFF, "%s", _command.c_str());
    system(_command.c_str());
}
//===============================================
GString2 GShell2::runSystem(const GString2& _command) {
    GLOGT(eGINF, "%s", _command.c_str());
    return runSystem(_command, getTmpDir(), getTmpInFilename(), getTmpOutFilename());
}
//===============================================
GString2 GShell2::runSystem(const GString2& _command, const GString2& _tmpDir, const GString2& _tmpInFile, const GString2& _tmpOutFile) {
    createDir(_tmpDir);
    GString2 lFilenameIn = sformat("%s/%s", _tmpDir.c_str(), _tmpInFile.c_str());
    GString2 lFilenameOut = sformat("%s/%s", _tmpDir.c_str(), _tmpOutFile.c_str());
    GFile2(lFilenameIn).setContent(_command);
    GString2 lCommand = sformat(". %s > %s", lFilenameIn.c_str(), lFilenameOut.c_str());
    runCommand(lCommand);
    GString2 lData = GFile2(lFilenameOut).getContent();
    return lData;
}
//===============================================
