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
    std::string lTmpFile = getLogFile("script", "txt");
    return lTmpFile;
}
//===============================================
std::string GShell::getLogFile(const std::string& _key, const std::string& _ext) const {
    GDate lDateObj;
    std::string lDate = lDateObj.getDate(lDateObj.getLogFormat());
    std::string lTmpFile = sformat("%s_%s.%s", _key.c_str(), lDate.c_str(), _ext.c_str());
    return lTmpFile;
}
//===============================================
void GShell::createDir(const std::string& _dir) {
    std::string lCommand = sformat("if ! [ -d %s ] ; then mkdir -p %s ; fi", _dir.c_str(), _dir.c_str());
    runSystem(lCommand);
}
//===============================================
void GShell::runSystem(const std::string& _command) {
    system(_command.c_str());
}
//===============================================
void GShell::runSystem(const std::string& _command, const std::string& _tmpDir, const std::string& _tmpFile) {
    createDir(_tmpDir);
    std::string lCommand = sformat("%s > %s/%s", _command.c_str(), _tmpDir.c_str(), _tmpFile.c_str());
    std::string lCommandEcho = sformat("cat %s/%s", _tmpDir.c_str(), _tmpFile.c_str());
    runSystem(lCommand);
    runSystem(lCommandEcho);
}
//===============================================
