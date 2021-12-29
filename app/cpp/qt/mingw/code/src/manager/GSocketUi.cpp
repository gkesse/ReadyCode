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
GSocketUi* GSocketUi::Create(const QString& _key) {
    if(_key == "default") {return new GSocketUi;}
    if(_key == "server") {return new GSocketServer;}
    if(_key == "client") {return new GSocketClient;}
    return new GSocketUi;
}
//===============================================
void GSocketUi::run(int _argc, char** _argv) {
    printf("[socket] process par defaut\n");
}
//===============================================
