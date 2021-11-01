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
    lOpenGL.blendOn();

    lOpenGL.onResize(onResize);
    lOpenGL.onKey(onKey);

    lOpenGL.shader2(lApp->shader_vertex_file, lApp->shader_fragment_file);
    lOpenGL.useProgram();

    lParams.bgcolor = {0.2f, 0.3f, 0.3f, 1.f};

    lOpenGL.pointsize(10.0f);
    lOpenGL.halfPi(lParams.angle);

    GObject lParticles;
    lParticles.particles();

    GOpenGL lParticlesTex;
    lParticlesTex.texture6(lApp->texture_file);
    lParticlesTex.texture(GL_TEXTURE0);

    lOpenGL.uniform2("ParticleTex", 0);
    lOpenGL.uniform("ParticleLifetime", 3.5f);
    lOpenGL.uniform("Gravity", glm::vec3(0.0f, -0.2f, 0.0f));

    while(!lOpenGL.isClose()) {
        lOpenGL.bgcolor2(lParams.bgcolor);

        lOpenGL.times(lParams.times);
        lOpenGL.uniform("Time", lParams.times);
        //lParams.mvp2.view.lookAt(3.0f * cos(lParams.angle), 1.5f, 3.0f * sin(lParams.angle), 0.0f, 1.5f, 0.0f, 0.0f, 1.0f, 0.0f);
        lParams.mvp2.view.identity;
        lParams.mvp2.model.identity();
        lParams.mvp2.mv.dot(lParams.mvp2.view, lParams.mvp2.model);
        lOpenGL.uniform("MVP", lParams.mvp2.projection.dot2(lParams.mvp2.mv));

        lParticles.render();

        lOpenGL.pollEvents();
    }

    lParticles.deletes();
    lOpenGL.close();
}
//===============================================
void GOpenGLUi::onResize(GLFWwindow* _window, int _width, int _height) {
    lOpenGL.viewport(_width, _height);
    //lParams.mvp2.projection.perspective(70.0f, 0.3f, 100.0f, _width, _height);
    lParams.mvp2.projection.identity();
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
