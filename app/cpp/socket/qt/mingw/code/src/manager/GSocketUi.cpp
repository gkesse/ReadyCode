//===============================================
#include "GSocketUi.h"
#include "GSocketServer.h"
#include "GSocketClient.h"
//===============================================
GSocketUi::GSocketUi(QObject* _parent) :
QObject(_parent) {

}
//===============================================
GSocketUi::~GSocketUi() {

}
//===============================================
GSocketUi* GSocketUi::Create(const QString& _key, QObject* _parent) {
    if(_key == "default") {return new GSocketUi(_parent);}
    if(_key == "server") {return new GSocketServer(_parent);}
    if(_key == "client") {return new GSocketClient(_parent);}
    return new GSocketUi(_parent);
}
//===============================================
void GSocketUi::run(int _argc, char** _argv) {
    printf("[socket] process par defaut\n");
}
//===============================================
