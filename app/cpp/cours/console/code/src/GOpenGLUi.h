//===============================================
#ifndef _GOpenGLUi_
#define _GOpenGLUi_
//===============================================
#include "GInclude.h"
//===============================================
class GOpenGLUi {
public:
	GOpenGLUi();
	virtual ~GOpenGLUi();
	static GOpenGLUi* Create(const std::string& key);
	virtual void run(int argc, char** argv);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow *window);

private:
	const unsigned int SCR_WIDTH = 400;
	const unsigned int SCR_HEIGHT = 400;

private:
	const char *vertexShaderSource =""
		"#version 330 core\n"
	    "layout (location = 0) in vec3 aPos;\n"
	    "void main()\n"
	    "{\n"
	    "   gl_Position = vec4(aPos, 1.0);\n"
	    "}\0";
	const char *fragmentShaderSource = ""
		"#version 330 core\n"
	    "out vec4 FragColor;\n"
	    "uniform vec4 ourColor;\n"
	    "void main()\n"
	    "{\n"
	    "   FragColor = ourColor;\n"
	    "}\n\0";
};
//==============================================
#endif
//==============================================
