//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
#include "GOpenGL.h"
//===============================================
GOpenGL GOpenGLUi::lOpenGL;
sGParams10 GOpenGLUi::lParams;
//===============================================
GOpenGLUi::GOpenGLUi() {

}
//===============================================
GOpenGLUi::~GOpenGLUi() {

}
//===============================================
GOpenGLUi* GOpenGLUi::Create(const std::string& key) {
    if(key == "default") {return new GOpenGLUi;}
    return new GOpenGLUi;
}
//===============================================
void GOpenGLUi::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->data()->app;

}
//===============================================
