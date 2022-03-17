//===============================================
#include "GConsole.h"
#include "GLog.h"
//===============================================
GConsole* GConsole::m_instance = 0;
//===============================================
GConsole::GConsole() : GObject() {

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
GConsole& GConsole::print(const std::string& _data) {
    printf("%s\n", _data.c_str());
    return *this;
}
//===============================================
GConsole& GConsole::print(const std::vector<std::string>& _data) {
    for(size_t i = 0; i < _data.size(); i++) {
        std::string lData = _data.at(i);
        printf("%s\n", lData.c_str());
    }
    return *this;
}
//===============================================
