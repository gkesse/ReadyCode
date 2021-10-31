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
	GLuint program();
	void use();
	void use(GLuint _programID);
	void depthOn();
	void depthOff();
	void onResize(GLFWframebuffersizefun _func);
	void onKey(GLFWkeyfun _func);
	void onKey();
	void onKey(bool& _animate);
	void onKey(GLfloat& _mixValue);
	void onKey(sGCamera& _cam, GLfloat& _deltaTime);
	void onKey(int action, int key, bool& _freeze, float& _alpha, float& _beta, float& _zoom);
	void onKey2(int action, int key, int _xsize, int _ysize, int _zsize, float& _pointsize, int& _xslice, int& _yslice, int& _zslice, float& _zoom);
	void viewport(int _width, int _height);
	void viewport(GLfloat _x, GLfloat _y, GLfloat _width, GLfloat _height);
	void info();
	void extensions();
	void debug();
	void debug2();
	static void APIENTRY onDebug(GLenum source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, const GLchar* _msg, const void* _param);
	void uniform(const char* _name, GLfloat _v0);
	void uniform(const char* _name, GLfloat _v0, GLfloat _v1, GLfloat _v2);
	void uniform(const char* _name, GLfloat _v0, GLfloat _v1, GLfloat _v2, GLfloat _v3);
	void uniform(const char* _name, const GLfloat* _v0);
	void uniform(const char* _name, const glm::vec3 &_vec);
	void uniform(const char* _name, const glm::vec4 &_vec);
	void uniform(const char* _name, const glm::mat4 &_mat);
	void uniform(const char* _name, const glm::mat3 &_mat);
	void uniform2(const char* _name, GLuint _v0);
	void uniform2(const char* _name, GLfloat _v0, GLfloat _v1, GLfloat _v2);
	void uniforms();
	void uniformBloc(const char* _name);
	void uniformBloc(int _size, const char** _names);
	void uniformBloc(int _offset, int _size, GLfloat* _data);
	void uniformBloc(GLuint _vbo);
	void uniformBloc();
	void uniformBlocs();
	const char* type(GLenum _type);

private:
	GLFWwindow* m_window;
	std::string m_title;
	int m_width;
	int m_height;
	GLuint m_programID;
	GLubyte* m_blockBuffer;
	GLint m_blockSize;
	GLuint* m_indices;
	GLint* m_offset;
};
//==============================================
#endif
//==============================================
