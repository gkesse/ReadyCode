//===============================================
#include "GServerUi.h"
#include "GManager.h"
//===============================================
GServerUi::GServerUi() {

}
//===============================================
GServerUi::~GServerUi() {

}
//===============================================
GServerUi* GServerUi::Create(const std::string& key) {
    if(key == "default") {return new GServerUi;}
    return new GServerUi;
}
//===============================================
void GServerUi::run(int _argc, char** _argv) {

}
//===============================================
