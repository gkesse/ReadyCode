//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
#include "GObject.h"
//===============================================
GOpenGL GOpenGLUi::lOpenGL;
sGOpenGL GOpenGLUi::lParams;
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
    lOpenGL.useProgram();

    lParams.bgcolor = {0.2f, 0.3f, 0.3f, 1.f};

    lOpenGL.uniform("Light.Intensity", glm::vec3(1.0f,1.0f,1.0f));
    lOpenGL.halfPi(lParams.angle);

    GObject lPlane;
    lPlane.plane(13.0f, 10.0f, 200, 2, 1.f, 1.f);
    lPlane.init();
    lPlane.clear();

    while(!lOpenGL.isClose()) {
        lOpenGL.bgcolor2(lParams.bgcolor);

        lOpenGL.times(lParams.times);
        lOpenGL.size(lParams.width, lParams.height);
        lOpenGL.uniform("Time", lParams.times);
        lParams.mvp2.view.lookAt(10.0f * cos(lParams.angle), 4.0f, 10.0f * sin(lParams.angle), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        lParams.mvp2.projection.perspective(60.0f, 0.3f, 100.0f, lParams.width, lParams.height);

        lOpenGL.uniform("Material.Kd", 0.9f, 0.5f, 0.3f);
        lOpenGL.uniform("Material.Ks", 0.8f, 0.8f, 0.8f);
        lOpenGL.uniform("Material.Ka", 0.2f, 0.2f, 0.2f);
        lOpenGL.uniform("Material.Shininess", 100.0f);

        lParams.mvp2.model.identity();
        lParams.mvp2.model.rotate(-10.0f, 0.0f, 0.0f, 1.0f);
        lParams.mvp2.model.rotate(50.0f, 1.0f, 0.0f, 0.0f);

        lParams.mvp2.mv.dot(lParams.mvp2.view, lParams.mvp2.model);
        lOpenGL.uniform("ModelViewMatrix", lParams.mvp2.mv.mat4());
        lOpenGL.uniform("NormalMatrix", lParams.mvp2.mv.mat3());
        lOpenGL.uniform("MVP", lParams.mvp2.projection.dot2(lParams.mvp2.mv));

        lPlane.render();

        lOpenGL.pollEvents();
    }

    lPlane.deletes();
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
