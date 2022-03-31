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
std::string GShell::getTmpFile() const {
    return GFile().getDateFilename("script", "txt");
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
void GShell::runSystem(const std::string& _command) {
    runSystem(_command, getTmpDir(), getTmpFile());
}
//===============================================
void GShell::runSystem(const std::string& _command, const std::string& _tmpDir, const std::string& _tmpFile) {
    createDir(_tmpDir);
    //
    std::string lDate = GDate().getDate("%d/%m/%Y - %H:%M:%S");
    std::string lFilename = sformat("%s/%s", _tmpDir.c_str(), _tmpFile.c_str());
    std::string lCommand = sformat("%s >> %s", _command.c_str(), lFilename.c_str());
    std::string lCommandSep = sformat("echo \"--->\" >> %s", lFilename.c_str());
    std::string lCommandEcho = sformat("echo \"%s\" >> %s", _command.c_str(), lFilename.c_str());
    std::string lCommandDate = sformat("echo \"===> %s\" >> %s", lDate.c_str(), lFilename.c_str());
    std::string lCommandCat = sformat("cat %s/%s", _tmpDir.c_str(), _tmpFile.c_str());
    //
    runCommand(lCommandDate);
    runCommand(lCommandEcho);
    runCommand(lCommandSep);
    runCommand(lCommand);
    runCommand(lCommandCat);
}
//===============================================
