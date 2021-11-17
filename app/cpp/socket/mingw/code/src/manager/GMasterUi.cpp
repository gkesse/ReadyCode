//===============================================
#include "GMasterUi.h"
#include "GSocketServer.h"
#include "GSocketClient.h"
//===============================================
GMasterUi::GMasterUi() {

}
//===============================================
GMasterUi::~GMasterUi() {

}
//===============================================
GMasterUi* GMasterUi::Create(const std::string& key) {
    if(key == "default") {return new GMasterUi;}
    return new GMasterUi;
}
//===============================================
void GMasterUi::run(int _argc, char** _argv) {
    printf("[master] process par defaut\n");
}
//===============================================
