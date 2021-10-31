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
bool GOpenGL::isClose() {
	return glfwWindowShouldClose(m_window);
}
//===============================================
void GOpenGL::close() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
//===============================================
void GOpenGL::pollEvents() {
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
//===============================================
void GOpenGL::bgcolor(const sGColor& _color) {
	glClearColor(_color.r, _color.g, _color.b, _color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}
//===============================================
void GOpenGL::bgcolor2(const sGColor& _color) {
	glClearColor(_color.r, _color.g, _color.b, _color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
void GOpenGL::info() {
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	GLint major, minor, samples, sampleBuffers;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	glGetIntegerv(GL_SAMPLES, &samples);
	glGetIntegerv(GL_SAMPLE_BUFFERS, &sampleBuffers);

	printf("-------------------------------------------------\n");
	printf("GL Vendor.......: %s\n", vendor);
	printf("GL Renderer.....: %s\n", renderer);
	printf("GL Version......: %s\n", version);
	printf("GL Version......: %d.%d\n", major, minor);
	printf("GLSL Version....: %s\n", glslVersion);
	printf("MSAA samples....: %d\n", samples);
	printf("MSAA buffers....: %d\n", sampleBuffers);
	printf("-------------------------------------------------\n");
}
//===============================================
void GOpenGL::extensions() {
	GLint nExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
	for( int i = 0; i < nExtensions; i++ ) {
		printf("Ext[%3d]........: %s\n", i, glGetStringi(GL_EXTENSIONS, i));
	}
}
//===============================================
void GOpenGL::debug() {
	glDebugMessageCallback(onDebug, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Start debugging");
}
//===============================================
void GOpenGL::debug2() {
	glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1, GL_DEBUG_SEVERITY_NOTIFICATION, -1, "End debug");
}
//===============================================
void APIENTRY GOpenGL::onDebug(GLenum source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, const GLchar* _msg, const void* _param) {
	std::string sourceStr;

	switch(source) {
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		sourceStr = "WindowSys";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		sourceStr = "App";
		break;
	case GL_DEBUG_SOURCE_API:
		sourceStr = "OpenGL";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		sourceStr = "ShaderCompiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		sourceStr = "3rdParty";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		sourceStr = "Other";
		break;
	default:
		sourceStr = "Unknown";
	}

	std::string typeStr;

	switch(_type) {
	case GL_DEBUG_TYPE_ERROR:
		typeStr = "Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		typeStr = "Deprecated";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		typeStr = "Undefined";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		typeStr = "Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		typeStr = "Performance";
		break;
	case GL_DEBUG_TYPE_MARKER:
		typeStr = "Marker";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		typeStr = "PushGrp";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		typeStr = "PopGrp";
		break;
	case GL_DEBUG_TYPE_OTHER:
		typeStr = "Other";
		break;
	default:
		typeStr = "Unknown";
	}

	std::string sevStr;

	switch(_severity) {
	case GL_DEBUG_SEVERITY_HIGH:
		sevStr = "HIGH";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		sevStr = "MED";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		sevStr = "LOW";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		sevStr = "NOTIFY";
		break;
	default:
		sevStr = "UNK";
	}

	std::cerr << sourceStr << ":" << typeStr << "[" << sevStr << "]" << "(" << _id << "): " << _msg << std::endl;
}
//===============================================
