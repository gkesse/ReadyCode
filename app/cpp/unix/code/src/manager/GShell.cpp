//===============================================
#include "GShell.h"
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
void GShell::initShell() {
    m_tmpPath       = GEnv().getTmpDir();
    m_currentDate   = GDate().getDateFileFormat();
    m_tmpInFile     = GFORMAT("%s/script_%s_in.txt", m_tmpPath.c_str(), m_currentDate.c_str());
    m_tmpOutFile    = GFORMAT("%s/script_%s_out.txt", m_tmpPath.c_str(), m_currentDate.c_str());
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
    createDir(m_tmpPath);
    GFile(m_tmpInFile).setContents(_command);
    GString lCommand = GFORMAT(". %s > %s", m_tmpInFile.c_str(), m_tmpOutFile.c_str());
    runCommand(lCommand);
    GString lData = GFile(m_tmpOutFile).getContents();
    return lData;
}
//===============================================
