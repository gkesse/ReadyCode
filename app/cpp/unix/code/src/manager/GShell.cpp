//===============================================
#include "GShell.h"
#include "GLog.h"
#include "GFormat.h"
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
std::string GShell::getTmpDir() const {
    return GEnv().getTmpDir();
}
//===============================================
std::string GShell::getTmpInFilename() const {
    return GFile().getScriptInFilename();
}
//===============================================
std::string GShell::getTmpOutFilename() const {
    return GFile().getScriptOutFilename();
}
//===============================================
void GShell::createDir(const std::string& _dir) {
    std::string lCommand = sformat("if ! [ -d %s ] ; then mkdir -p %s ; fi", _dir.c_str(), _dir.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell::cleanDir(const std::string& _dir) {
    std::string lCommand = sformat("if [ -d %s ] ; then rm -rf %s/* ; fi", _dir.c_str(), _dir.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell::runCommand(const std::string& _command) {
    system(_command.c_str());
}
//===============================================
std::string GShell::runSystem(const std::string& _command) {
    GLOGT(eGMSG, "%s", _command.c_str());
    return runSystem(_command, getTmpDir(), getTmpInFilename(), getTmpOutFilename());
}
//===============================================
std::string GShell::runSystem(const std::string& _command, const std::string& _tmpDir, const std::string& _tmpInFile, const std::string& _tmpOutFile) {
    createDir(_tmpDir);
    std::string lFilenameIn = sformat("%s/%s", _tmpDir.c_str(), _tmpInFile.c_str());
    std::string lFilenameOut = sformat("%s/%s", _tmpDir.c_str(), _tmpOutFile.c_str());
    GFile(lFilenameIn).setContent(_command);
    std::string lCommand = sformat(". %s > %s", lFilenameIn.c_str(), lFilenameOut.c_str());
    runCommand(lCommand);
    std::string lData = GFile(lFilenameOut).getContent();
    return lData;
}
//===============================================
