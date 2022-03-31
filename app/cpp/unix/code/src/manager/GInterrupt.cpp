//===============================================
#include "GInterrupt.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GInterrupt::GInterrupt() : GObject() {

}
//===============================================
GInterrupt::~GInterrupt() {

}
//===============================================
void GInterrupt::setCallback(void* _onInterrupt) {
    m_sigaction.sa_handler = (GSIGNAL_CB)_onInterrupt;
    sigemptyset(&m_sigaction.sa_mask);
    m_sigaction.sa_flags = 0;
    sigaction(SIGINT, &m_sigaction, NULL);
}
//===============================================
void GInterrupt::onInterrupt(int _signo) {
    GLOGT(eGINF, "interruption du programme...\n");
}
//===============================================
