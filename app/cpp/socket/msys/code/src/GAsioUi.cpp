//===============================================
#include "GAsioUi.h"
#include "GAsioServer.h"
#include "GAsioClient.h"
//===============================================
GAsioUi::GAsioUi() {

}
//===============================================
GAsioUi::~GAsioUi() {

}
//===============================================
GAsioUi* GAsioUi::Create(const std::string& key) {
    if(key == "default") {return new GAsioUi;}
    if(key == "server") {return new GAsioServer;}
    if(key == "client") {return new GAsioClient;}
    return new GAsioUi;
}
//===============================================
void GAsioUi::run(int argc, char** argv) {
    printf("[asio] process par defaut\n");
}
//===============================================
