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

	lParams.bgcolor = {0.1f, 0.2f, 0.3f, 1.0f};
	lParams.mvp.projection = glm::mat4(1.0f);

    GLfloat lVertices[] = {
        -1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
    };
    GLfloat lTextCoord[] = {
        0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
        0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
    };

    lOpenGL.init3();
    lOpenGL.depthOn();
    lOpenGL.onResize(onResize);
    lOpenGL.shader(lApp->shader_vertex_file, lApp->shader_fragment_file);
    lOpenGL.use();

    lOpenGL.vao(1, lParams.vao);
    lOpenGL.vbo(2, lParams.vbo);

    lOpenGL.vao(lParams.vao[0]);
    lOpenGL.vbo(lParams.vbo[0], lVertices, sizeof(lVertices));
    lOpenGL.vbo(0, 3, 3, 0);
    lOpenGL.vbo(lParams.vbo[1], lTextCoord, sizeof(lTextCoord));
    lOpenGL.vbo(2, 2, 2, 0);

    lOpenGL.uniform("Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    lOpenGL.uniform2("NoiseTex", 0);

    lParams.slice = glm::rotate(lParams.slice, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0));
    lParams.slice = glm::rotate(lParams.slice, glm::radians(-20.0f), glm::vec3(0.0,0.0,1.0));
    lParams.slice = glm::scale(lParams.slice, glm::vec3(40.0, 40.0, 1.0));
    lParams.slice = glm::translate(lParams.slice, glm::vec3(-0.35, -0.5, 2.0));

    lOpenGL.uniform("Slice", lParams.slice);

    lParams.noise.baseFreq = 4.0f;
    lParams.noise.persistence = 0.5f;
    lParams.noise.width = 128;
    lParams.noise.height = 128;
    lParams.noise.periodic = false;

    lOpenGL.vao(0);

    GFunction lNoise;
    lNoise.noise(lParams.noise);
    lOpenGL.texture(lNoise.noise(), lParams.noise.width, lParams.noise.height);
    lNoise.deleteNoise();

    lOpenGL.texture(GL_TEXTURE0);

    while (!lOpenGL.isClose()) {
        lOpenGL.bgcolor2(lParams.bgcolor);
        lParams.mvp.view = glm::mat4(1.0f);
        lParams.mvp.model = glm::mat4(1.0f);
        lOpenGL.uniform("MVP", lParams.mvp.projection * lParams.mvp.view * lParams.mvp.model);
        lOpenGL.vao(lParams.vao[0]);
        lOpenGL.triangle(0, 6);
        glFinish();
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
