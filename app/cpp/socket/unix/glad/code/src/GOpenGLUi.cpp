//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
//===============================================
GOpenGL GOpenGLUi::lOpenGL;
sGOpenCV GOpenGLUi::lParams;
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

    lOpenGL.init(4, 5, 4);

    lParams.bgcolor = {0.1f, 0.2f, 0.3f, 1.f};

    lOpenGL.info();
    lOpenGL.debug();

    while(!lOpenGL.isClose()) {
    	lOpenGL.bgcolor2(lParams.bgcolor);

    	lOpenGL.pollEvents();
    }

    lOpenGL.debug2();
    lOpenGL.close();
}
//===============================================
