//===============================================
#include "GConsole.h"
//===============================================
GConsole* GConsole::m_instance = 0;
//===============================================
GConsole::GConsole(QObject* _parent) : GObject(_parent) {

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
void GConsole::printData(const QString& _data) {
    printf("%s\n", _data.toStdString().c_str());
}
//===============================================
