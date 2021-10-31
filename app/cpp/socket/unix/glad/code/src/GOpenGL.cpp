//===============================================
#include "GOpenGL.h"
#include "GFile.h"
//===============================================
GOpenGL::GOpenGL() {
	m_window = 0;
	m_title = "ReadyApp";
	m_width = 400;
	m_height = 400;
	m_programID = 0;
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
void GOpenGL::shader(const std::string& _vertexCode, const std::string& _fragmentCode) {
	GLuint lVertexId = glCreateShader(GL_VERTEX_SHADER);
	compile(lVertexId, _vertexCode);

	GLuint lFragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	compile(lFragmentId, _fragmentCode);

	m_programID = glCreateProgram();

	glAttachShader(m_programID, lVertexId);
	glAttachShader(m_programID, lFragmentId);
	glLinkProgram(m_programID);

	GLint lResult = 0;
	int logLength;

	glGetProgramiv(m_programID, GL_LINK_STATUS, &lResult);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLength);

	glDeleteShader(lVertexId);
	glDeleteShader(lFragmentId);
}
//===============================================
void GOpenGL::shader2(const std::string& _vertexFile, const std::string& _fragmentFile) {
	GFile lFile;
	lFile.filename(_vertexFile);
	std::string lVertexCode = lFile.read();
	lFile.filename(_fragmentFile);
	std::string lFragmentCode = lFile.read();
	shader(lVertexCode, lFragmentCode);
}
//===============================================
void GOpenGL::shader3(const std::string& _shaderFile, GLenum _shaderType) {
	GFile lFile;
	GLint lStatus;

	lFile.filename(_shaderFile);
	const char* lShaderCode[] = {lFile.read().c_str()};
	m_programID = glCreateShaderProgramv(_shaderType, 1, lShaderCode);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &lStatus);
}
//===============================================
void GOpenGL::shader4(const std::string& _shaderFile, GLenum _shaderType) {
	GFile lFile;
	GLint lStatus;

	lFile.filename(_shaderFile);
	std::string lShaderCode = lFile.read();
	GLuint lShaderId = glCreateShader(_shaderType);
	compile(lShaderId, lShaderCode);
	m_programID = glCreateProgram();
	glProgramParameteri(m_programID, GL_PROGRAM_SEPARABLE, GL_TRUE);
	glAttachShader(m_programID, lShaderId);
	glLinkProgram(m_programID);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &lStatus);
}
//===============================================
void GOpenGL::compile(GLuint _shaderId, const std::string& _code) {
	GLint lResult = 0;
	GLint lLength;
	const char* lCode = _code.c_str();
	glShaderSource(_shaderId, 1, &lCode , NULL);
	glCompileShader(_shaderId);
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &lResult);
	glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &lLength);
}
//===============================================
void GOpenGL::use() {
	glUseProgram(m_programID);
}
//===============================================
void GOpenGL::use(GLuint _programID) {
	glUseProgram(_programID);
}
//===============================================
void GOpenGL::depthOn() {
	glEnable(GL_DEPTH_TEST);
}
//===============================================
void GOpenGL::depthOff() {
	glDisable(GL_DEPTH_TEST);
}
//===============================================
void GOpenGL::onResize(GLFWframebuffersizefun _func) {
	glfwSetFramebufferSizeCallback(m_window, _func);
	_func(m_window, m_width, m_height);
}
//===============================================
void GOpenGL::onKey(GLFWkeyfun _func) {
	glfwSetKeyCallback(m_window, _func);
}
//===============================================
void GOpenGL::onKey() {
	if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_window, true);
	}
}
//===============================================
void GOpenGL::onKey(bool& _animate) {
	if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_window, true);
	}
	if(glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		_animate = !_animate;
	}
}
//===============================================
void GOpenGL::onKey(GLfloat& _mixValue) {
	if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_window, true);
	}

	if(glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS) {
		_mixValue += 0.01f;
		if(_mixValue >= 1.0f) {
			_mixValue = 1.0f;
		}
	}

	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		_mixValue -= 0.01f;
		if (_mixValue <= 0.0f) {
			_mixValue = 0.0f;
		}
	}
}
//===============================================
void GOpenGL::onKey(sGCamera& _cam, GLfloat& _deltaTime) {
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_window, true);
	}

	_cam.speed = _cam.speedFactor * _deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS) {
		_cam.eye += _cam.speed * _cam.front;
	}
	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		_cam.eye -= _cam.speed * _cam.front;
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		_cam.eye -= glm::normalize(glm::cross(_cam.front, _cam.up)) * _cam.speed;
	}
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		_cam.eye += glm::normalize(glm::cross(_cam.front, _cam.up)) * _cam.speed;
	}
}
//===============================================
void GOpenGL::onKey(int action, int key, bool& _freeze, float& _alpha, float& _beta, float& _zoom) {
	if (action != GLFW_PRESS) {return;}
	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(m_window, GL_TRUE);
		break;
	case GLFW_KEY_SPACE:
		_freeze = !_freeze;
		break;
	case GLFW_KEY_LEFT:
		_alpha += 5.0f;
		break;
	case GLFW_KEY_RIGHT:
		_alpha -= 5.0f;
		break;
	case GLFW_KEY_UP:
		_beta -= 5.0f;
		break;
	case GLFW_KEY_DOWN:
		_beta += 5.0f;
		break;
	case GLFW_KEY_PAGE_UP:
		_zoom -= 0.25f;
		if (_zoom < 0.0f) {_zoom = 0.0f;}
		break;
	case GLFW_KEY_PAGE_DOWN:
		_zoom += 0.25f;
		break;
	default:
		break;
	}
}
//===============================================
void GOpenGL::onKey2(int action, int key, int _xsize, int _ysize, int _zsize, float& _pointsize, int& _xslice, int& _yslice, int& _zslice, float& _zoom) {
	if (action != GLFW_PRESS) {return;}
	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(m_window, GL_TRUE);
		break;
	case GLFW_KEY_P:
		_pointsize += 0.5;
		break;
	case GLFW_KEY_O:
		_pointsize -= 0.5;
		break;
	case GLFW_KEY_A:
		_yslice -=1;
		if(_yslice < 0)
			_yslice = 0;
		break;
	case GLFW_KEY_D:
		_yslice +=1;
		if(_yslice >= _ysize - 1)
			_yslice = _ysize - 1;
		break;
	case GLFW_KEY_W:
		_zslice +=1;
		if(_zslice >= _zsize - 1)
			_zslice = _zsize - 1;
		break;
	case GLFW_KEY_S:
		_zslice -= 1;
		if (_zslice < 0)
			_zslice = 0;
		break;
	case GLFW_KEY_E:
		_xslice -=1;
		if(_xslice < 0)
			_xslice = 0;
		break;
	case GLFW_KEY_Q:
		_xslice +=1;
		if(_xslice >= _xsize - 1)
			_xslice = _xsize - 1;
		break;
	case GLFW_KEY_PAGE_UP:
		_zoom -= 0.25f;
		if (_zoom < 0.0f) {_zoom = 0.0f;}
		break;
	case GLFW_KEY_PAGE_DOWN:
		_zoom += 0.25f;
		break;
	default:
		break;
	}
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
