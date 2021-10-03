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

    float lSigma = 0.01f;

    while (!lOpenGL.isClose()) {
        lOpenGL.viewport();
        lOpenGL.grid(5.f, 1.f, 0.1f);
        lOpenGL.axis(5.f, 1.f , 5.f, {1.f, 1.f, 1.f, 0.5f});
        lSigma += 0.01f;
        if(lSigma > 1.0f) {lSigma = 0.01;}
        lOpenGL.gaussian2D(1000, 1000, lSigma, 2.f);
        lOpenGL.pollEvents();
    }

    lOpenGL.close();
}
//===============================================
