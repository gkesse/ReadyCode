//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
#include "GObject.h"
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

    lParams.mvp2.model.identity();
    lParams.mvp2.model.rotate(-35.0f, 1.0f, 0.0f, 0.0f);
    lParams.mvp2.model.rotate(35.0f, 0.0f, 1.0f, 0.0f);
    lParams.mvp2.view.lookAt(0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    lOpenGL.uniform("Kd", 0.9f, 0.5f, 0.3f);
    lOpenGL.uniform("Ld", 1.0f, 1.0f, 1.0f);
    lOpenGL.uniform("LightPosition", lParams.mvp2.view.dot(5.0f, 5.0f, 2.0f, 1.0f));

    GObject lTorus;
    lTorus.torus(0.7f, 0.3f, 30, 30);
    lTorus.init();

    lOpenGL.info();
    lOpenGL.debug();

    while(!lOpenGL.isClose()) {
    	lOpenGL.bgcolor2(lParams.bgcolor);
        lParams.mvp2.mv.dot(lParams.mvp2.view, lParams.mvp2.model);
        lOpenGL.uniform("ModelViewMatrix", lParams.mvp2.mv.mat4());
        lOpenGL.uniform("NormalMatrix", lParams.mvp2.mv.mat3());
        lParams.mvp2.mvp.dot(lParams.mvp2.projection, lParams.mvp2.mv);
        lOpenGL.uniform("MVP", lParams.mvp2.mvp.mat4());
        lTorus.render();
    	lOpenGL.pollEvents();
    }

    lOpenGL.debug2();
    lTorus.deletes();
    lOpenGL.close();
}
//===============================================
void GOpenGLUi::onResize(GLFWwindow* _window, int _width, int _height) {
    lOpenGL.viewport(_width,_height);
    lParams.mvp2.projection.perspective(70.0f, 0.3f, 100.0f, _width, _height);
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
