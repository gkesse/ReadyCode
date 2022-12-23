//===============================================
#include "GDate.h"
#include "GShell.h"
#include "GEnv.h"
#include "GFile.h"
//===============================================
GShell::GShell()
: GObject() {
    initShell();
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
    if(_dir == "") return;
    GString lCommand = GFORMAT("if ! [ -d %s ] ; then mkdir -p %s ; fi", _dir.c_str(), _dir.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell::tailFile(const GString& _file) {
    if(_file == "") return;
    GString lCommand = GFORMAT("if [ -e %s ] ; then tail -f %s ; fi", _file.c_str(), _file.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell::cleanDir(const GString& _dir) {
    if(_dir == "") return;
    GString lCommand = GFORMAT("if [ -d %s ] ; then rm -rf %s/* ; fi", _dir.c_str(), _dir.c_str());
    runCommand(lCommand);
}
//===============================================
void GShell::runCommand(const GString& _command) {
    system(_command.c_str());
}
//===============================================
GString GShell::runSystem(const GString& _command) {
    GLOGT(eGINF, _command.c_str());
    createDir(m_tmpPath);
    GFile(m_tmpInFile).setContents(_command);
    GString lCommand = GFORMAT(". %1 > %2", m_tmpInFile.c_str(), m_tmpOutFile.c_str());
    runCommand(lCommand);
    GString lData = GFile(m_tmpOutFile).getContent();
    return lData;
}
//===============================================
