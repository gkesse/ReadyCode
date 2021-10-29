//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
#include "GOpenGL.h"
#include "GFunction.h"
#include "data_ecg.h"
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

    lOpenGL.init2();
    lOpenGL.depthOn();
    lOpenGL.onResize(onResize);

    GOpenGL lFragment1, lFragment2, lPipeline1, lPipeline2;
    lOpenGL.shader3(lApp->shader_vertex_file, GL_VERTEX_SHADER);
    lFragment1.shader3(lApp->shader_fragment_file, GL_FRAGMENT_SHADER);
    lFragment2.shader3(lApp->shader_fragment_file_2, GL_FRAGMENT_SHADER);
    lPipeline1.pipeline(lOpenGL, lFragment1);
    lPipeline2.pipeline(lOpenGL, lFragment2);

    lParams.bgcolor = {0.1f, 0.2f, 0.3f, 1.0f};

    GLfloat lVertices[] = {
            -0.8f, -0.8f, 0.0f,
            0.8f, -0.8f, 0.0f,
            0.0f,  0.8f, 0.0f
    };
    GLfloat lColors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
    };

    lOpenGL.vao(1, lParams.vao);
    lOpenGL.vbo(2, lParams.vbo);

    lOpenGL.vao(lParams.vao[0]);
    lOpenGL.vbo(lParams.vbo[0], lVertices, sizeof(lVertices));
    lOpenGL.vbo(0, 3, 3, 0);
    lOpenGL.vbo(lParams.vbo[1], lColors, sizeof(lColors));
    lOpenGL.vbo(1, 3, 3, 0);

    while (!lOpenGL.isClose()) {
        lOpenGL.bgcolor2(lParams.bgcolor);
        lOpenGL.use(0);
        lOpenGL.uniform2("uColorMask", 0.0f, 1.0f, 0.0f);
        lOpenGL.vao(lParams.vao[0]);
        lOpenGL.viewport(0.f, 0.f, 0.5f, 1.f);
        lPipeline1.pipeline();
        lOpenGL.triangle(0, 3);
        lOpenGL.viewport(0.5f, 0.f, 0.5f, 1.f);
        lPipeline2.pipeline();
        lOpenGL.triangle(0, 3);
        lOpenGL.pollEvents();
    }

    lOpenGL.close();
}
//===============================================
void GOpenGLUi::onResize(GLFWwindow* _window, int _width, int _height) {
    lOpenGL.viewport(_width, _height);
}
//===============================================
void GOpenGLUi::onKey(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {

}
//===============================================
void GOpenGLUi::onScroll(GLFWwindow* _window, double _x, double _y) {

}
//===============================================
void GOpenGLUi::onMouse(GLFWwindow* _window, int _button, int _action, int _mods) {

}
//===============================================
void GOpenGLUi::onCursor(GLFWwindow* _window, double _x, double _y) {

}
//===============================================
void GOpenGLUi::onDisplay() {

}
//===============================================
