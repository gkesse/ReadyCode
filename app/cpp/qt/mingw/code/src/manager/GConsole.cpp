//===============================================
#include "GConsole.h"
#include "GThread.h"
//===============================================
GConsole* GConsole::m_instance = 0;
//===============================================
GConsole::GConsole() : GObject() {
    m_consoleOn = true;
    m_readyOn = true;
    m_console = 0;
    m_pseudo = "unknown";
}
//===============================================
GConsole::~GConsole() {

}
//===============================================
GConsole* GConsole::Instance() {
    if(m_instance == 0) {
        m_instance = new GConsole;
    }
    return m_instance;
}
//===============================================
void GConsole::runConsole() {
    GThread lThread;
    lThread.createThread(onRunConsole, this);
}
//===============================================
GConsole* GConsole::getConsole() const {
    return m_console;
}
//===============================================
void GConsole::stopConsole() {
    m_consoleOn = false;
}
//===============================================
void GConsole::setPseudo(const std::string& _pseudo) {
    m_pseudo = _pseudo;
}
//===============================================
std::queue<std::string>& GConsole::getDataIn() {
    return m_dataIn;
}
//===============================================
bool& GConsole::getReadyOn() {
    return m_readyOn;
}
//===============================================
DWORD WINAPI GConsole::onRunConsole(LPVOID _params) {
    GConsole* lConsole = (GConsole*)_params;

    while(lConsole->m_consoleOn) {
        if(lConsole->m_readyOn) {
            printf("===> (%s)\n> ", lConsole->m_pseudo.c_str());
            std::string lData;
            std::getline(std::cin, lData);
            lConsole->m_dataIn.push(lData);
            lConsole->m_readyOn = false;
        }
   }

    return 0;
}
//===============================================
