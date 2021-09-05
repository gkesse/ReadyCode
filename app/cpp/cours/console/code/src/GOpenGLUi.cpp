//===============================================
#include "GOpenGLUi.h"
// window
#include "GWindowCreate.h"
#include "GWindowClear.h"
//===============================================
GOpenGLUi::GOpenGLUi() {

}
//===============================================
GOpenGLUi::~GOpenGLUi() {

}
//===============================================
GOpenGLUi* GOpenGLUi::Create(const std::string& key) {
    if(key == "default") {return new GOpenGLUi;}
    // window
    if(key == "window/create") {return new GWindowCreate;}
    if(key == "window/clear") {return new GWindowClear;}
    // default
    return new GOpenGLUi;
}
//===============================================
void GOpenGLUi::run(int argc, char** argv) {
    std::cout << "[opengl] aucun process n'a ete selectionne.\n";
}
//===============================================

