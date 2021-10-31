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
    lOpenGL.depthOn();
    lOpenGL.onResize(onResize);
    lOpenGL.onKey(onKey);

    lOpenGL.shader2(lApp->shader_vertex_file, lApp->shader_fragment_file);
    lOpenGL.use();

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
void GOpenGLUi::onResize(GLFWwindow* _window, int _width, int _height) {
    glViewport(0,0,_width,_height);
    lParams.mvp.projection = glm::perspective(glm::radians(70.0f), (float)_width/_height, 0.3f, 100.0f);
}
//===============================================
void GOpenGLUi::onKey(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {
    lOpenGL.onKey(lParams.animate);
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
