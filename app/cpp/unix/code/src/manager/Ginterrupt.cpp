//===============================================
#include "GInterrupt.h"
//===============================================
GInterrupt::GInterrupt() : GObject() {

}
//===============================================
GInterrupt::~GInterrupt() {

}
//===============================================
void GInterrupt::setCallback(void* _onInterrupt) {
    m_sigaction.sa_handler = (GINTERRUPT_CB)_onInterrupt;
    sigemptyset(&m_sigaction.sa_mask);
    m_sigaction.sa_flags = 0;
    sigaction(SIGINT, &m_sigaction, NULL);
}
//===============================================
void GInterrupt::onInterrupt(int _signo) {
    printf("=====>\n");
    printf("interruption du programme...\n");
}
//===============================================
