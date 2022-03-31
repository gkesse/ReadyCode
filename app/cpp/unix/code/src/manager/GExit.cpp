//===============================================
#include "GExit.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GExit::GExit() : GObject() {

}
//===============================================
GExit::~GExit() {

}
//===============================================
void GExit::setCallback(void* _onExit) {
    atexit((GEXIT_CB)_onExit);
}
//===============================================
void GExit::onExit() {
    GLOGT(eGINF, "sortie du programme...\n");
}
//===============================================
