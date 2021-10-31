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
	printf("%d - %d", fbw, fbh);
	//gladLoadGL();
}
//===============================================
