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
void GConsole::printData(bool _data) {
    if(_data) {
        printf("true\n");
    }
    else {
        printf("false\n");
    }
}
//===============================================
void GConsole::printData(const char* _data) {
    printf("%s\n", _data);
}
//===============================================
void GConsole::printData(int _data) {
    printf("%d\n", _data);
}
//===============================================
void GConsole::printData(const QString& _data) {
    printf("%s\n", _data.toStdString().c_str());
}
//===============================================
