//===============================================
#ifndef _GOpenGL_
#define _GOpenGL_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
#include "GFunction.h"
//===============================================
class GOpenGL {
public:
	GOpenGL();
	~GOpenGL();
	void init(int _major, int _minor, int _samples);
	bool isClose();
	void close();
	void pollEvents();
	void bgcolor(const sGColor& _color);
	void bgcolor2(const sGColor& _color);
	sGColor heatMap(float _v, float _vmin, float _vmax, const sGColor& _color);
	void shader(const std::string& _vertexCode, const std::string& _fragmentCode);
	void shader2(const std::string& _vertexFile, const std::string& _fragmentFile);
	void shader3(const std::string& _shaderFile, GLenum _shaderType);
	void shader4(const std::string& _shaderFile, GLenum _shaderType);
	void compile(GLuint _shaderId, const std::string& _code);
	void use();
	void use(GLuint _programID);
	void depthOn();
	void depthOff();
	void onResize(GLFWframebuffersizefun _func);
	void onKey(GLFWkeyfun _func);
	void onKey();
	void GOpenGL::onKey(bool& _animate);
	void onKey(GLfloat& _mixValue);
	void onKey(sGCamera& _cam, GLfloat& _deltaTime);
	void onKey(int action, int key, bool& _freeze, float& _alpha, float& _beta, float& _zoom);
	void onKey2(int action, int key, int _xsize, int _ysize, int _zsize, float& _pointsize, int& _xslice, int& _yslice, int& _zslice, float& _zoom);
	void info();
	void extensions();
	void debug();
	void debug2();
	static void APIENTRY onDebug(GLenum source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, const GLchar* _msg, const void* _param);

private:
	GLFWwindow* m_window;
	std::string m_title;
	int m_width;
	int m_height;
	GLuint m_programID;
};
//==============================================
#endif
//==============================================
