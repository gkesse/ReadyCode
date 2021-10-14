//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
#include "GOpenGL.h"
#include "GFunction.h"
#include "data_ecg.h"
//===============================================
GOpenGL GOpenGLUi::lOpenGL;
sGParams9 GOpenGLUi::lParams;
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
    lOpenGL.onResize(onResize);
    lOpenGL.onKey(onKey);

    lParams.color = {0.2f, 0.3f, 0.3f, 1.f};
    lParams.cam.eye = glm::vec3(0.f, 0.f, 3.f);
    lParams.cam.front = glm::vec3(0.f, 0.f, -1.f);
    lParams.cam.up = glm::vec3(0.f, 1.f, 0.f);
    lParams.deltaTime = 0.f;
    lParams.lastTime = 0.f;

    GOpenGL lOpenGL2;

    lOpenGL.shader2(lApp->shader_vertex_file, lApp->shader_fragment_file);
    lOpenGL.texture2(lApp->texture_file);
    lOpenGL2.texture3(lApp->texture_file2);

    float lVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    glm::vec3 lCubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    lOpenGL.vao(1, &lParams.vao);
    lOpenGL.vbo(1, &lParams.vbo);
    lOpenGL.vbo(1, &lParams.ebo);

    lOpenGL.vao(lParams.vao);
    lOpenGL.vbo(lParams.vbo, lVertices, sizeof(lVertices));
    lOpenGL.vbo(0, 3, 5, 0);
    lOpenGL.vbo(1, 2, 5, 3);

    lOpenGL.use();
    lOpenGL.uniform2("texture1", 0);
    lOpenGL.uniform2("texture2", 1);

    lOpenGL2.depthOn();

    while(!lOpenGL.isClose()) {
        lOpenGL.bgcolor2(lParams.color);
        lOpenGL.use();
        lOpenGL.texture(GL_TEXTURE0);
        lOpenGL2.texture(GL_TEXTURE1);
        lOpenGL.vao(lParams.vao);

		GLfloat lCurrentTime = glfwGetTime();
		lParams.deltaTime = lCurrentTime - lParams.lastTime;
		lParams.lastTime = lCurrentTime;

        lParams.cam.center = lParams.cam.eye + lParams.cam.front;
        lParams.mvp.view = lOpenGL.camera(lParams.cam);
        lOpenGL.uniform("view", glm::value_ptr(lParams.mvp.view));

        lParams.mvp.projection = glm::perspective(glm::radians(45.0f), (float)lOpenGL.width() / (float)lOpenGL.height(), 0.1f, 100.0f);
        lOpenGL.uniform("projection", glm::value_ptr(lParams.mvp.projection));

        for (int i = 0; i < 10; i++) {
        	lParams.mvp.model = glm::mat4(1.0f);
        	lParams.mvp.model = glm::translate(lParams.mvp.model, lCubePositions[i]);
            lParams.angle = 20.0f * (i + 1);
            lParams.mvp.model = glm::rotate(lParams.mvp.model, glm::radians(lParams.angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lOpenGL.uniform("model", glm::value_ptr(lParams.mvp.model));
            lOpenGL.triangle(0, 36);
        }

        lOpenGL.pollEvents();
    }

    lOpenGL.deleteVao(1, &lParams.vao);
    lOpenGL.deleteVbo(1, &lParams.vbo);
    lOpenGL.deleteTexture();
    lOpenGL2.deleteTexture();
    lOpenGL.deleteProgram();
    lOpenGL.close();
}
//===============================================
void GOpenGLUi::onResize(GLFWwindow* _window, int _width, int _height) {
    lOpenGL.viewport(_width, _height);
}
//===============================================
void GOpenGLUi::onKey(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {
    lOpenGL.onKey(lParams.cam, lParams.deltaTime);
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
