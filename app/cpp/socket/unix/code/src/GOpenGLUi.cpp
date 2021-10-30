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

	lOpenGL.init(4, 5, 4);
	lOpenGL.depthOn();
	lOpenGL.onResize(onResize);
	lOpenGL.onKey(onKey);

	lOpenGL.shader2(lApp->shader_vertex_file, lApp->shader_fragment_file);
	lOpenGL.use();

	lParams.bgcolor = {0.1f, 0.2f, 0.3f, 1.0f};
	lParams.animate = true;
	lParams.angle = 0.f;

	float lVertices[] = {
			-0.8f, -0.8f, 0.0f,
			0.8f, -0.8f, 0.0f,
			0.8f,  0.8f, 0.0f,
			-0.8f, -0.8f, 0.0f,
			0.8f, 0.8f, 0.0f,
			-0.8f, 0.8f, 0.0f
	};
	GLfloat lTextures[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
	};

	lOpenGL.vao(1, lParams.vao);
	lOpenGL.vbo(3, lParams.vbo);

	lOpenGL.vao(lParams.vao[0]);
	lOpenGL.vbo(lParams.vbo[0], lVertices, sizeof(lVertices));
	lOpenGL.vbo(0, 3, 0, 0);
	lOpenGL.vbo(lParams.vbo[1], lTextures, sizeof(lTextures));
	lOpenGL.vbo(1, 2, 0, 0);

	const char* lBlobSettings[] = {
			"BlobSettings.InnerColor",
			"BlobSettings.OuterColor",
			"BlobSettings.RadiusInner",
			"BlobSettings.RadiusOuter"
	};

	GLfloat lInnerColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
	GLfloat lOuterColor[] = {1.0f, 1.0f, 0.75f, 1.0f};
	GLfloat lRadiusInner[] = {0.25f};
	GLfloat lRadiusOuter[] = {0.45f};

	lOpenGL.uniformBloc("BlobSettings");
	lOpenGL.uniformBloc(4, lBlobSettings);
	lOpenGL.uniformBloc(0, 4, lInnerColor);
	lOpenGL.uniformBloc(1, 4, lOuterColor);
	lOpenGL.uniformBloc(2, 1, lRadiusInner);
	lOpenGL.uniformBloc(3, 1, lRadiusOuter);
	lOpenGL.uniformBloc(lParams.vbo[2]);
	lOpenGL.uniformBloc();

	while (!lOpenGL.isClose()) {
		lOpenGL.bgcolor2(lParams.bgcolor);
		lOpenGL.angle(lParams.animate, lParams.angle);
		lOpenGL.rotation(lParams.rotation, lParams.angle);
		lOpenGL.uniform("RotationMatrix", &lParams.rotation[0][0]);
		lOpenGL.vao(lParams.vao[0]);
		lOpenGL.triangle(0, 6);
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
