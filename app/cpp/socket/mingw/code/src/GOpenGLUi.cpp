//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
#include "GOpenGL.h"
#include "GFunction.h"
#include "data_ecg.h"
//===============================================
GOpenGL GOpenGLUi::lOpenGL;
sGParams3 GOpenGLUi::lParams;
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

    const GLfloat lVertices[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f
    };
    const GLfloat lColors[] = {
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
    };

    lParams.vertex = lVertices;
    lParams.color = lColors;
    lParams.vertex_size = sizeof(lVertices);
    lParams.color_size = sizeof(lColors);

    lOpenGL.init2();

    lOpenGL.shader(lApp->vertex_shader_file, lApp->fragment_shader_file);

    lOpenGL.vao(1, &lParams.vao);
    lOpenGL.vbo(1, &lParams.vbo_vertex);
    lOpenGL.vbo(1, &lParams.vbo_color);
    lOpenGL.vbo(lParams.vbo_vertex, lParams.vertex, lParams.vertex_size);
    lOpenGL.vbo(lParams.vbo_color, lParams.color, lParams.color_size);
    lOpenGL.vbo(lParams.vbo_vertex, lParams.attrib_vertex, "position");
    lOpenGL.vbo(lParams.vbo_color, lParams.attrib_color, "color_in");
    lOpenGL.fragment(0, "color_out");

    lOpenGL.use();

    while (!lOpenGL.isClose()) {
    	lOpenGL.bgcolor();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        lOpenGL.pollEvents();
    }

    lOpenGL.disableAttrib(lParams.attrib_vertex);
    lOpenGL.disableAttrib(lParams.attrib_color);
    lOpenGL.deleteVbo(1, &lParams.vbo_vertex);
    lOpenGL.deleteVbo(1, &lParams.vbo_color);
    lOpenGL.deleteVao(1, &lParams.vao);
    lOpenGL.deleteProgram();
    lOpenGL.close();
}
//===============================================
void GOpenGLUi::onResize(GLFWwindow* _window, int _width, int _height) {

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
