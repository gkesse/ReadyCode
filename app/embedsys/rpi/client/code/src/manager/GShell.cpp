//===============================================
#include "GShell.h"
//===============================================
GShell::GShell() {

}
//===============================================
GShell::~GShell() {
    clearMap();
}
//===============================================
void GShell::runSystem(const GString& _cmd) {
    if(_cmd.isEmpty()) return;
    GString lCmd = sformat("%s > /dev/null 2>&1", _cmd.c_str());
    system(lCmd.c_str());
}
//===============================================
GString GShell::runCmd(const GString& _cmd) {
    if(_cmd.isEmpty()) return "";
    std::array<char, 256> lBuffer;
    std::string lResult;
    std::unique_ptr<FILE, decltype(&pclose)> lPipe(popen(_cmd.c_str(), "r"), pclose);
    if(!lPipe) {
        throw std::runtime_error("Le shell n'est pas initialisé.");
    }
    while(fgets(lBuffer.data(), lBuffer.size(), lPipe.get()) != nullptr) {
        lResult += lBuffer.data();
        if(lResult.size() >= BUFFER_MAX) {
            m_logs.addLog("La taille maximale des données est atteinte.");
            break;
        }
    }
    return lResult;
}
//===============================================
