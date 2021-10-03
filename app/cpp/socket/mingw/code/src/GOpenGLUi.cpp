//===============================================
#include "GOpenGLUi.h"
#include "GOpenGL.h"
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
    GOpenGL lOpenGL;
    lOpenGL.init();

    float lPhase = 0.f;

    while (!lOpenGL.isClose()) {
        lOpenGL.viewport();
        lOpenGL.grid(5.f, 1.f, 0.1f);
        lOpenGL.axis(5.f, 1.f , 5.f, {1.f, 1.f, 1.f, 0.5f});
        lPhase += 0.02f;
        lOpenGL.sinus(0.8f, lPhase, 200, 10.f);
        lOpenGL.pollEvents();
    }

    lOpenGL.close();
}
//===============================================
