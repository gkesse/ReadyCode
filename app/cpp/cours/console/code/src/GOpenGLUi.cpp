//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
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
	sGApp* lApp = GManager::Instance()->getData()->app;

	glfwSetErrorCallback(onError);

	if (!glfwInit()) {
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ReadyApp", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return;
	}

	glfwSetKeyCallback(window, onKey);

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, onResize);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//===============================================
		// code de l'application
		//===============================================
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
//===============================================
void GOpenGLUi::onResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
//===============================================
void GOpenGLUi::onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
//===============================================
void GOpenGLUi::onError(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}
//===============================================
