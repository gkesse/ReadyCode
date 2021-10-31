//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
#include "GOpenGL.h"
#include "GFunction.h"
#include "GObject.h"
//===============================================
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

    lOpenGL.init(4, 5, 4);
    lOpenGL.depthOn();
    lOpenGL.onResize(onResize);
    lOpenGL.onKey(onKey);

    lOpenGL.shader2(lApp->shader_vertex_file, lApp->shader_fragment_file);
    lOpenGL.use();

    lParams.bgcolor = {0.1f, 0.2f, 0.3f, 1.0f};

    lParams.mvp2.model.identity();
    lParams.mvp2.model.rotate(-35.0f, 1.0f, 0.0f, 0.0f);
    lParams.mvp2.model.rotate(35.0f, 0.0f, 1.0f, 0.0f);
    lParams.mvp2.view.lookAt(0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    lParams.mvp2.projection.identity();

    /*lParams.mvp.model = glm::mat4(1.0f);
    lParams.mvp.model = glm::rotate(lParams.mvp.model, glm::radians(-35.0f), glm::vec3(1.0f,0.0f,0.0f));
    lParams.mvp.model = glm::rotate(lParams.mvp.model, glm::radians(35.0f), glm::vec3(0.0f,1.0f,0.0f));
    lParams.mvp.view = glm::lookAt(glm::vec3(0.0f,0.0f,2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    lParams.mvp.projection = glm::mat4(1.0f);*/

    lOpenGL.uniform("Kd", 0.9f, 0.5f, 0.3f);
    lOpenGL.uniform("Ld", 1.0f, 1.0f, 1.0f);
    lOpenGL.uniform("LightPosition", lParams.mvp2.view.dot(5.0f, 5.0f, 2.0f, 1.0f));

    /*lOpenGL.uniform("Kd", 0.9f, 0.5f, 0.3f);
    lOpenGL.uniform("Ld", 1.0f, 1.0f, 1.0f);
    lOpenGL.uniform("LightPosition", lParams.mvp.view * glm::vec4(5.0f,5.0f,2.0f,1.0f));*/

    GObject lTorus;
    lTorus.torus(0.7f, 0.3f, 30, 30);
    lTorus.init();

    lOpenGL.info();
    lOpenGL.debug();

    while (!lOpenGL.isClose()) {
        lOpenGL.bgcolor2(lParams.bgcolor);
        lParams.mvp2.mv.dot(lParams.mvp2.view, lParams.mvp2.model);
        lOpenGL.uniform("ModelViewMatrix", lParams.mvp2.mv.mat4());
        lOpenGL.uniform("NormalMatrix", lParams.mvp2.mv.mat3());
        lParams.mvp2.mvp.dot(lParams.mvp2.projection, lParams.mvp2.mv);
        lOpenGL.uniform("MVP", lParams.mvp2.mvp.mat4());
        /*glm::mat4 mv = lParams.mvp.view * lParams.mvp.model;
        lOpenGL.uniform("ModelViewMatrix", mv);
        lOpenGL.uniform("NormalMatrix", glm::mat3( glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]) ));
        lOpenGL.uniform("MVP", lParams.mvp.projection * mv);*/
        lTorus.render();
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
void GOpenGLUi::onDisplay() {

}
//===============================================
