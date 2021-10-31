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
    lOpenGL.use();

    lParams.bgcolor = {0.2f, 0.3f, 0.3f, 1.f};

    lParams.noise.baseFreq = 4.0f;
    lParams.noise.persistence = 0.5f;
    lParams.noise.width = 128;
    lParams.noise.height = 128;
    lParams.noise.periodic = false;

    GLfloat lVertices[] = {
        -1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
    };
    GLfloat lTexCoords[] = {
        0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
        0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
    };

    lOpenGL.vao(1, lParams.vao);
    lOpenGL.vbo(2, lParams.vbo);

    lOpenGL.vao(lParams.vao[0]);
    lOpenGL.vbo(lParams.vbo[0], lVertices, sizeof(lVertices));
    lOpenGL.vbo(0, 3, 3, 0);
    lOpenGL.vbo(lParams.vbo[1], lTexCoords, sizeof(lTexCoords));
    lOpenGL.vbo(1, 2, 2, 0);

    lOpenGL.uniform("Color", glm::vec4(1.0f,0.0f,0.0f,1.0f));
    lOpenGL.uniform2("NoiseTex", 0);

    lParams.slice.identity();
    lParams.slice.rotate(10.0f, 1.0, 0.0, 0.0);
    lParams.slice.rotate(-20.0f, 0.0, 0.0, 1.0);
    lParams.slice.scale(40.0, 40.0, 1.0);
    lParams.slice.translate(-0.35, -0.5, 2.0);

    lOpenGL.uniform("Slice", lParams.slice.mat4());

    GFunction lNoiseFunc;
    GOpenGL lNoiseTex;
    lNoiseFunc.noise(lParams.noise);
    lNoiseTex.texture(lNoiseFunc.noise(), lParams.noise.width, lParams.noise.height);
    lNoiseTex.texture(GL_TEXTURE0);
    lNoiseFunc.deleteNoise();

    while(!lOpenGL.isClose()) {
        lOpenGL.bgcolor2(lParams.bgcolor);
        lParams.mvp2.view.identity();
        lParams.mvp2.model.identity();
        lParams.mvp2.mv.dot(lParams.mvp2.view, lParams.mvp2.model);
        lOpenGL.uniform("MVP", lParams.mvp2.projection.dot2(lParams.mvp2.mv));
        lOpenGL.vao(lParams.vao[0]);
        lOpenGL.triangle(0, 6);
        lOpenGL.pollEvents();
    }

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
