//===============================================
#include "GCppUi.h"
#include "GClass.h"
#include "GClassA.h"
#include "GClassB.h"
#include "GClassC.h"
//===============================================
GCppUi::GCppUi() {

}
//===============================================
GCppUi::~GCppUi() {

}
//===============================================
GCppUi* GCppUi::Create(const std::string& _key) {
    if(_key == "default") {return new GCppUi;}
    return new GCppUi;
}
//===============================================
void GCppUi::run(int _argc, char** _argv) {
    GClass* lLed = new GClassA;
    GClass* lButton = new GClassB;
    lButton->addObserver(lLed);
    lButton->on();
    lButton->on();
}
//===============================================
