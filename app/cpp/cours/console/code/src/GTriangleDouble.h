//===============================================
#ifndef _GTriangleDouble_
#define _GTriangleDouble_
//===============================================
#include "GOpenGLUi.h"
//===============================================
class GTriangleDouble : public GOpenGLUi {
public:
	GTriangleDouble();
	virtual ~GTriangleDouble();
	virtual void run(int argc, char** argv);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);

private:
	const unsigned int SCR_WIDTH = 400;
	const unsigned int SCR_HEIGHT = 400;

private:
	const char *vertexShaderSource = ""
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\n";
	const char *fragmentShaderSource = ""
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n";
};
//==============================================
#endif
//==============================================
