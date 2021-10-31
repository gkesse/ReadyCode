//===============================================
#define STB_IMAGE_IMPLEMENTATION
//===============================================
#include "GOpenGL.h"
#include "GFile.h"
//===============================================
#include <stb_image.h>
//===============================================
GOpenGL::GOpenGL() {
	m_window = 0;
	m_title = "ReadyApp";
	m_width = 400;
	m_height = 400;
	m_programID = 0;
	m_textureID = 0;
	m_blockBuffer = 0;
	m_blockSize = 0;
	m_indices = 0;
	m_offset = 0;
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
void GOpenGL::texture(GLenum _texture) {
	glActiveTexture(_texture);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
//===============================================
void GOpenGL::texture(const std::string& _image) {
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int lWidth, lHeight, lChannels;

	unsigned char* lData = stbi_load(_image.c_str(), &lWidth, &lHeight, &lChannels, 0);

	if(lData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lWidth, lHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, lData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(lData);
}
//===============================================
void GOpenGL::texture(GLubyte* _data, int _width, int _height) {
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA, _width, _height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, _data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
//===============================================
void GOpenGL::texture2(const std::string& _image) {
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int lWidth, lHeight, lChannels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* lData = stbi_load(_image.c_str(), &lWidth, &lHeight, &lChannels, 0);

	if(lData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lWidth, lHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, lData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(lData);
}
//===============================================
void GOpenGL::texture3(const std::string& _image) {
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int lWidth, lHeight, lChannels;

	unsigned char* lData = stbi_load(_image.c_str(), &lWidth, &lHeight, &lChannels, 0);

	if(lData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lWidth, lHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, lData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(lData);
}
//===============================================
void GOpenGL::texture4(const std::string& _image) {
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int lWidth, lHeight, lChannels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* lData = stbi_load(_image.c_str(), &lWidth, &lHeight, &lChannels, 0);

	if(lData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lWidth, lHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, lData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(lData);
}
//===============================================
void GOpenGL::texture5(const std::string& _image) {
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int lWidth, lHeight, lChannels;

	unsigned char* lData = stbi_load(_image.c_str(), &lWidth, &lHeight, &lChannels, 0);

	if(lData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lWidth, lHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, lData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(lData);
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
GLuint GOpenGL::program() {
	return m_programID;
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
void GOpenGL::vao(GLuint _vao) {
	glBindVertexArray(_vao);
}
//===============================================
void GOpenGL::vao(GLsizei _n, GLuint* _vao) {
	glGenVertexArrays(_n, _vao);
}
//===============================================
void GOpenGL::vbo(GLuint _vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}
//===============================================
void GOpenGL::vbo(GLsizei _n, GLuint* _vbo) {
	glGenBuffers(_n, _vbo);
}
//===============================================
void GOpenGL::vbo(GLuint _vbo, const void* _data, GLsizeiptr _size) {
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _size, _data, GL_STATIC_DRAW);
}
//===============================================
void GOpenGL::vbo(GLuint _vbo, const char* _name) {
	GLint lLocation = glGetAttribLocation(m_programID, _name);
	glEnableVertexAttribArray(lLocation);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(lLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}
//===============================================
void GOpenGL::vbo(GLuint _vbo, GLuint& _attrib, const char* _name) {
	_attrib = glGetAttribLocation(m_programID, _name);
	glEnableVertexAttribArray(_attrib);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(_attrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}
//===============================================
void GOpenGL::vbo(GLuint _location, GLint _size, GLsizei _stride, GLuint _pointer) {
	glVertexAttribPointer(_location, _size, GL_FLOAT, GL_FALSE, _stride * sizeof(GLfloat), (void*)(_pointer * sizeof(GLfloat)));
	glEnableVertexAttribArray(_location);
}
//===============================================
void GOpenGL::vbo2(GLuint _location, GLuint _vbo, GLintptr _offset, GLsizei _stride) {
	glBindVertexBuffer(_location, _vbo, _offset, _stride * sizeof(GLfloat));
	glEnableVertexAttribArray(_location);
}
//===============================================
void GOpenGL::vbo2(GLuint _ebo, const void* _data, GLsizeiptr _size) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size, _data, GL_STATIC_DRAW);
}
//===============================================
void GOpenGL::deleteVao(GLsizei _n, GLuint* _vao) {
	glDeleteVertexArrays(_n, _vao);
}
//===============================================
void GOpenGL::deleteVbo(GLsizei _n, GLuint* _vbo) {
	glDeleteBuffers(_n, _vbo);
}
//===============================================
void GOpenGL::disableAttrib(GLuint _attrib) {
	glDisableVertexAttribArray(_attrib);
}
//===============================================
void GOpenGL::deleteProgram() {
	if(m_programID) {
		glDeleteProgram(m_programID);
		m_programID = 0;
	}
}
//===============================================
void GOpenGL::deleteTexture() {
	if(m_textureID) {
		glDeleteTextures(1, &m_textureID);
		m_textureID = 0;
	}
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
void GOpenGL::triangle(GLint _index, GLsizei _count) {
	glDrawArrays(GL_TRIANGLES, _index, _count);
}
//===============================================
void GOpenGL::triangle2(const void* _indices, GLsizei _count) {
	glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, _indices);
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
void GOpenGL::viewport(int _width, int _height) {
	glViewport(0, 0, _width, _height);
}
//===============================================
void GOpenGL::viewport(GLfloat _x, GLfloat _y, GLfloat _width, GLfloat _height) {
	int lX = (int)(_x * m_width);
	int lY = (int)(_y * m_height);
	int lWidth = (int)(_width * m_width);
	int lHeight = (int)(_height * m_height);
	glViewport(lX, lY, lWidth, lHeight);
}
//===============================================
void GOpenGL::angle(bool _animate, float& _angle, float _step) {
	if(_animate) {
		_angle += _step;
		if(_angle >= 360.0f) _angle -= 360.0f;
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
void GOpenGL::uniform(const char* _name, GLfloat _v0) {
	GLint lLocation = glGetUniformLocation(m_programID, _name);
	glUniform1f(lLocation, _v0);
}
//===============================================
void GOpenGL::uniform(const char* _name, GLfloat _v0, GLfloat _v1, GLfloat _v2) {
	GLint lLocation = glGetUniformLocation(m_programID, _name);
	glUniform3f(lLocation, _v0, _v1, _v2);
}
//===============================================
void GOpenGL::uniform(const char* _name, GLfloat _v0, GLfloat _v1, GLfloat _v2, GLfloat _v3) {
	GLint lLocation = glGetUniformLocation(m_programID, _name);
	glUniform4f(lLocation, _v0, _v1, _v2, _v3);
}
//===============================================
void GOpenGL::uniform(const char* _name, const GLfloat* _v0) {
	GLint lLocation = glGetUniformLocation(m_programID, _name);
	glUniformMatrix4fv(lLocation, 1, GL_FALSE, _v0);
}
//===============================================
void GOpenGL::uniform(const char* _name, const glm::vec3& _vec) {
	uniform(_name, _vec.x, _vec.y, _vec.z);
}
//===============================================
void GOpenGL::uniform(const char* _name, const glm::vec4& _vec) {
	uniform(_name, _vec.x, _vec.y, _vec.z, _vec.w);
}
//===============================================
void GOpenGL::uniform(const char* _name, const glm::mat4& _mat) {
	GLint lLocation = glGetUniformLocation(m_programID, _name);
	glUniformMatrix4fv(lLocation, 1, GL_FALSE, &_mat[0][0]);
}
//===============================================
void GOpenGL::uniform(const char* _name, const glm::mat3& _mat) {
	GLint lLocation = glGetUniformLocation(m_programID, _name);
	glUniformMatrix3fv(lLocation, 1, GL_FALSE, &_mat[0][0]);
}
//===============================================
void GOpenGL::uniform2(const char* _name, GLuint _v0) {
	GLint lLocation = glGetUniformLocation(m_programID, _name);
	glUniform1i(lLocation, _v0);
}
//===============================================
void GOpenGL::uniform2(const char* _name, GLfloat _v0, GLfloat _v1, GLfloat _v2) {
	GLint lLocation = glGetUniformLocation(m_programID, _name);
	glProgramUniform3f(m_programID, lLocation, _v0, _v1, _v2);
}
//===============================================
void GOpenGL::uniformBloc(const char* _name) {
	GLuint lLocation = glGetUniformBlockIndex(m_programID, _name);
	glGetActiveUniformBlockiv(m_programID, lLocation, GL_UNIFORM_BLOCK_DATA_SIZE, &m_blockSize);
	m_blockBuffer = new GLubyte[m_blockSize];
}
//===============================================
void GOpenGL::uniformBloc(int _size, const char** _names) {
	m_indices = new GLuint[_size];
	m_offset = new GLint[_size];
	glGetUniformIndices(m_programID, _size, _names, m_indices);
	glGetActiveUniformsiv(m_programID, _size, m_indices, GL_UNIFORM_OFFSET, m_offset);
}
//===============================================
void GOpenGL::uniformBloc(int _offset, int _size, GLfloat* _data) {
	memcpy(m_blockBuffer + m_offset[_offset], _data, _size * sizeof(GLfloat));
}
//===============================================
void GOpenGL::uniformBloc(GLuint _vbo) {
	glBindBuffer(GL_UNIFORM_BUFFER, _vbo);
	glBufferData( GL_UNIFORM_BUFFER, m_blockSize, m_blockBuffer, GL_DYNAMIC_DRAW);
	glBindBufferBase( GL_UNIFORM_BUFFER, 1, _vbo);
}
//===============================================
void GOpenGL::uniformBloc() {
	delete[] m_blockBuffer;
	delete[] m_indices;
	delete[] m_offset;
}
//===============================================
void GOpenGL::uniforms() {
	GLint numUniforms = 0;
	glGetProgramInterfaceiv(m_programID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);
	GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};

	printf("Active uniforms.....:\n");
	for( int i = 0; i < numUniforms; ++i ) {
		GLint results[4];
		glGetProgramResourceiv(m_programID, GL_UNIFORM, i, 4, properties, 4, NULL, results);
		if( results[3] != -1 ) continue;
		GLint nameBufSize = results[0] + 1;
		char * name = new char[nameBufSize];
		glGetProgramResourceName(m_programID, GL_UNIFORM, i, nameBufSize, NULL, name);
		printf(".....[%-5d] : %s (%s)\n", results[2], name, type(results[1]));
		delete [] name;
	}
}
//===============================================
void GOpenGL::uniformBlocs() {
	GLint numBlocks = 0;
	glGetProgramInterfaceiv(m_programID, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &numBlocks);
	GLenum blockProps[] = {GL_NUM_ACTIVE_VARIABLES, GL_NAME_LENGTH};
	GLenum blockIndex[] = {GL_ACTIVE_VARIABLES};
	GLenum props[] = {GL_NAME_LENGTH, GL_TYPE, GL_BLOCK_INDEX};

	for(int block = 0; block < numBlocks; ++block) {
		GLint blockInfo[2];
		glGetProgramResourceiv(m_programID, GL_UNIFORM_BLOCK, block, 2, blockProps, 2, NULL, blockInfo);
		GLint numUnis = blockInfo[0];

		char * blockName = new char[blockInfo[1]+1];
		glGetProgramResourceName(m_programID, GL_UNIFORM_BLOCK, block, blockInfo[1]+1, NULL, blockName);
		printf("Uniform block.....: \"%s\":\n", blockName);
		delete [] blockName;

		GLint* unifIndexes = new GLint[numUnis];
		glGetProgramResourceiv(m_programID, GL_UNIFORM_BLOCK, block, 1, blockIndex, numUnis, NULL, unifIndexes);

		for( int unif = 0; unif < numUnis; ++unif ) {
			GLint uniIndex = unifIndexes[unif];
			GLint results[3];
			glGetProgramResourceiv(m_programID, GL_UNIFORM, uniIndex, 3, props, 3, NULL, results);

			GLint nameBufSize = results[0] + 1;
			char * name = new char[nameBufSize];
			glGetProgramResourceName(m_programID, GL_UNIFORM, uniIndex, nameBufSize, NULL, name);
			printf(".....: %s (%s)\n", name, type(results[1]));
			delete[] name;
		}

		delete[] unifIndexes;
	}
}
//===============================================
const char* GOpenGL::type(GLenum _type) {
	switch (_type) {
	case GL_FLOAT: return "float";
	case GL_FLOAT_VEC2: return "vec2";
	case GL_FLOAT_VEC3: return "vec3";
	case GL_FLOAT_VEC4: return "vec4";
	case GL_DOUBLE: return "double";
	case GL_INT: return "int";
	case GL_UNSIGNED_INT: return "unsigned int";
	case GL_BOOL: return "bool";
	case GL_FLOAT_MAT2: return "mat2";
	case GL_FLOAT_MAT3: return "mat3";
	case GL_FLOAT_MAT4: return "mat4";
	default: return "?";
	}
}
//===============================================
