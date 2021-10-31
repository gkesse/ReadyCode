//===============================================
#include "GOpenGL.h"
//===============================================
GOpenGL::GOpenGL() {
	m_window = 0;
	m_title = "ReadyApp";
	m_width = 400;
	m_height = 400;
}
//===============================================
GOpenGL::~GOpenGL() {

}
//===============================================
void GOpenGL::init(int _major, int _minor, int _samples) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, _samples);
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(m_window);
	int fbw, fbh;
	glfwGetFramebufferSize(m_window, &fbw, &fbh);
	gladLoadGL();
}
//===============================================
sGColor GOpenGL::heatMap(float _v, float _vmin, float _vmax, const sGColor& _color) {
	sGColor lColor = _color;
	float dv = _vmax - _vmin;
	if (_v < (_vmin + 0.25f * dv)) {
		lColor.r = 0.0f;
		lColor.g = 4.0f * (_v - _vmin) / dv;
	}
	else if (_v < (_vmin + 0.5f * dv)) {
		lColor.r = 0.0f;
		lColor.b = 1.0f + 4.0f * (_vmin + 0.25f * dv - _v) / dv;
	}
	else if (_v < (_vmin + 0.75f * dv)) {
		lColor.r = 4.0f * (_v - _vmin - 0.5f * dv) / dv;
		lColor.b = 0.0f;
	}
	else {
		lColor.g = 1.0f + 4.0f * (_vmin + 0.75f * dv - _v) / dv;
		lColor.b = 0.0f;
	}
	return lColor;
}
//===============================================
