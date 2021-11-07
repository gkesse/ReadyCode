//===============================================
#include "GSocketUi.h"
#include "GSocketServer.h"
#include "GSocketClient.h"
//===============================================
GSocketUi::GSocketUi() {

}
//===============================================
GSocketUi::~GSocketUi() {

}
//===============================================
GSocketUi* GSocketUi::Create(const std::string& key) {
    if(key == "default") {return new GSocketUi;}
    if(key == "server") {return new GSocketServer;}
    if(key == "client") {return new GSocketClient;}
    return new GSocketUi;
}
//===============================================
void GSocketUi::run(int _argc, char** _argv) {
    printf("[opengl] process par defaut\n");
}
//===============================================
