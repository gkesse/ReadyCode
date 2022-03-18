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
GConsole& GConsole::printData(bool _data) {
    if(_data) {
        printf("true\n");
    }
    else {
        printf("false\n");
    }
    return *this;
}
//===============================================
GConsole& GConsole::printData(int _data) {
    printf("%d\n", _data);
    return *this;
}
//===============================================
GConsole& GConsole::printData(const char* _data) {
    printf("%s\n", _data);
    return *this;
}
//===============================================
GConsole& GConsole::printData(const std::string& _data) {
    printf("%s\n", _data.c_str());
    return *this;
}
//===============================================
GConsole& GConsole::printData(const std::vector<std::string>& _data) {
    for(size_t i = 0; i < _data.size(); i++) {
        std::string lData = _data.at((int)i);
        printf("%s\n", lData.c_str());
    }
    return *this;
}
//===============================================
