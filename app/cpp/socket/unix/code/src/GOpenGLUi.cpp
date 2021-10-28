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

	lOpenGL.init3();
	lOpenGL.depthOn();
	lOpenGL.shader(lApp->shader_vertex_file, lApp->shader_fragment_file);
	lOpenGL.use();
	lOpenGL.info();

	lParams.bgcolor = {0.1f, 0.2f, 0.3f, 1.0f};

	float lVertices[] = {
			-0.8f, -0.8f, 0.0f,
			0.8f, -0.8f, 0.0f,
			0.0f,  0.8f, 0.0f
	};
	float lColors[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
	};

	lOpenGL.vao(1, lParams.vao);
	lOpenGL.vbo(2, lParams.vbo);

	lOpenGL.vao(lParams.vao[0]);
	lOpenGL.vbo(lParams.vbo[0], lVertices, 9 * sizeof(float));
	lOpenGL.vbo(0, 3, 0, 0);
	lOpenGL.vbo(lParams.vbo[1], lColors, 9 * sizeof(float));
	lOpenGL.vbo(1, 3, 0, 0);
	lOpenGL.vao(0);

	while (!lOpenGL.isClose()) {
		lOpenGL.bgcolor2(lParams.bgcolor);
		lOpenGL.vao(lParams.vao[0]);
		lOpenGL.triangle(0, 3);
		lOpenGL.vao(0);
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
