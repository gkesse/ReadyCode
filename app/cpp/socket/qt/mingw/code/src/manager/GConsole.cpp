//===============================================
#include "GConsole.h"
//===============================================
GConsole* GConsole::m_instance = 0;
//===============================================
GConsole::GConsole() {

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
void GConsole::showData(const std::string& _data) {
    printf("%s\n", _data.c_str());
}
//===============================================
void GConsole::showData(const std::vector<std::string>& _data) {
    for(size_t i = 0; i < _data.size(); i++) {
        if(i != 0) printf(" ; ");
        std::string lData = _data.at(i);
        printf("%s", lData.c_str());
    }
    printf("\n");
}
//===============================================
void GConsole::showData(const std::vector<std::vector<std::string>>& _data) {
    for(size_t i = 0; i < _data.size(); i++) {
        std::vector<std::string> lRow = _data.at(i);
        for(size_t j = 0; j < lRow.size(); j++) {
            if(j != 0) printf(" ; ");
            std::string lData = lRow.at(j);
            printf("%s", lData.c_str());
        }
        printf("\n");
    }
}
//===============================================
