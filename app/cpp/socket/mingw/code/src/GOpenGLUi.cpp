//===============================================
#include "GOpenGLUi.h"
#include "GOpenGL.h"
#include "data_ecg.h"
//===============================================
GOpenGL GOpenGLUi::lOpenGL;
sGParams GOpenGLUi::lParams;
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
    lOpenGL.init();
    lOpenGL.onResize(onResize);
    lOpenGL.onKey(onKey);
    lOpenGL.onScroll(onScroll);

    lParams.sigma = 0.1f;
    lParams.sign = 1.0f;
    lParams.step = 0.01f;
    lParams.alpha = 210.0f;
    lParams.beta = -70.0f;
    lParams.zoom = 2.0f;
    lParams.lock = false;
    lParams.freeze = false;

    while (!lOpenGL.isClose()) {
        lOpenGL.position(lParams.alpha, lParams.beta, lParams.zoom);
        lOpenGL.grid(5.f, 1.f, 0.1f);
        lOpenGL.axis(5.f, 1.f , 5.f, {1.f, 1.f, 1.f, 0.5f});
        if(!lParams.freeze) {
            lParams.sigma = lParams.sigma + lParams.sign*lParams.step;
            if(lParams.sigma > 1.0f) {lParams.sign = -1.0f;}
            if(lParams.sigma < 0.1){lParams.sign = 1.0f;}
        }
        lOpenGL.gaussian2D(1000, 1000, lParams.sigma, 2.f);
        lOpenGL.pollEvents();
    }

    lOpenGL.close();
}
//===============================================
void GOpenGLUi::onResize(GLFWwindow* _window, int _width, int _height) {
    lOpenGL.camera(45.f, 0.1f, 128.f, _width, _height);
}
//===============================================
void GOpenGLUi::onKey(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {
    lOpenGL.onKey(_action, _key, lParams.freeze, lParams.alpha, lParams.beta, lParams.zoom);
}
//===============================================
void GOpenGLUi::onScroll(GLFWwindow* _window, double _x, double _y) {
	lOpenGL.onScroll(_x, _y, lParams.zoom);
}
//===============================================
