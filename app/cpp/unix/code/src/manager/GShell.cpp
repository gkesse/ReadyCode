//===============================================
#include "GShell.h"
#include "GLog.h"
#include "GFormat.h"
#include "GEnv.h"
#include "GDate.h"
//===============================================
GShell::GShell() : GObject() {

}
//===============================================
GShell::~GShell() {

}
//===============================================
std::string GShell::getTmpDir() const {
    GEnv lEnv;
    std::string lTmpDir = lEnv.getEnv("GPROJECT_TMP");
    if(lTmpDir == "") {
        GERROR("Erreur la methode (GShell::getTmpDir) a echoue.");
        return "";
    }
    return lTmpDir;
}
//===============================================
std::string GShell::getTmpFile() const {
    GDate lDateObj;
    std::string lDate = lDateObj.getDate("%Y_%m_%d");
    std::string lTmpFile = getLogFile("script", lDate.c_str(), "txt");
    return lTmpFile;
}
//===============================================
std::string GShell::getLogFile(const std::string& _key, const std::string& _date, const std::string& _ext) const {
    std::string lFilename = sformat("%s_%s.%s", _key.c_str(), _date.c_str(), _ext.c_str());
    return lFilename;
}
//===============================================
void GShell::createDir(const std::string& _dir) {
    std::string lCommand = sformat("if ! [ -d %s ] ; then mkdir -p %s ; fi", _dir.c_str(), _dir.c_str());
    runSystem(lCommand);
}
//===============================================
void GShell::cleanDir(const std::string& _dir) {
    std::string lCommand = sformat("if [ -d %s ] ; then rm -rf %s/* ; fi", _dir.c_str(), _dir.c_str());
    runSystem(lCommand);
}
//===============================================
void GShell::runSystem(const std::string& _command) {
    system(_command.c_str());
}
//===============================================
void GShell::runSystem(const std::string& _command, const std::string& _tmpDir, const std::string& _tmpFile) {
    createDir(_tmpDir);
    GDate lDateObj;
    //
    std::string lDate = lDateObj.getDate("%d/%m/%Y - %H:%M:%S");
    std::string lFilename = sformat("%s/%s", _tmpDir.c_str(), _tmpFile.c_str());
    std::string lCommand = sformat("%s >> %s", _command.c_str(), lFilename.c_str());
    std::string lCommandSep = sformat("echo \"----->\" >> %s", lFilename.c_str());
    std::string lCommandEcho = sformat("echo \"%s\" >> %s", _command.c_str(), lFilename.c_str());
    std::string lCommandDate = sformat("echo \"=====> %s\" >> %s", lDate.c_str(), lFilename.c_str());
    std::string lCommandCat = sformat("cat %s/%s", _tmpDir.c_str(), _tmpFile.c_str());
    //
    runSystem(lCommandDate);
    runSystem(lCommandEcho);
    runSystem(lCommandSep);
    runSystem(lCommand);
    runSystem(lCommandCat);
}
//===============================================
