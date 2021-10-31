//===============================================
#ifndef _GOpenGL_
#define _GOpenGL_
//===============================================
#include "GInclude.h"
#include "GFunction.h"
#include "GStruct.h"
//===============================================
class GOpenGL {
public:
	typedef void APIENTRY (*onDebugCB)(GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, const GLchar* _msg, const void* _param);

public:
	GOpenGL();
	~GOpenGL();
	int width();
	void width(int _width);
	int height();
	void height(int _height);
	void title(const std::string& _title);
	void init(int _major, int _minor, int _samples);
	void info();
	void extensions();
	void bgcolor(const sGColor& _color);
	void bgcolor2(const sGColor& _color);
	void onKey(GLFWkeyfun _func);
	void onKey();
	void onKey(bool& _animate);
	void onKey(GLfloat& _mixValue);
	void onKey(sGCamera& _cam, GLfloat& _deltaTime);
	void onKey(int action, int key, bool& _freeze, float& _alpha, float& _beta, float& _zoom);
	void onKey2(int action, int key, int _xsize, int _ysize, int _zsize, float& _pointsize, int& _xslice, int& _yslice, int& _zslice, float& _zoom);
	void onResize(GLFWframebuffersizefun _func);
	void onMouse(GLFWmousebuttonfun _func);
	void onMouse(int _button, int _action, bool& lock);
	void onCursor(GLFWcursorposfun _func);
	void onCursor(double _x, double _y, bool& _lock, float& _alpha, float& _beta, int _cursorX, int& _cursorY);
	void onScroll(GLFWscrollfun _func);
	void onScroll(double _x, double _y, float& _zoom);
	void coordinate(sGCamera& _cam, GLfloat _rho, GLfloat _theta, GLfloat _phi);
	void normal(GLfloat* _vertex, GLfloat* _normal, int& _ncircle, int& _nvertex, float _pointsize);
	void vector(GLfloat* _vertex, GLfloat* _normal, float _pointsize);
	void indices(sGParams4& _params);
	void loop();
	bool isClose();
	void close();
	void pollEvents();
	void viewport();
	void viewport(int _width, int _height);
	void viewport(GLfloat _x, GLfloat _y, GLfloat _width, GLfloat _height);
	void viewport(int _x, int _y, int _width, int _height);
	void point(const sGVertex& _obj, int _width);
	void point();
	void point(GFunction& _func, float _psize);
	void line(const sGVertex* _obj, int _width);
	void line(const sGVertex& _v1, const sGVertex& _v2, int _width);
	void line(GFunction& _func, float _linesize);
	void grid(float _width, float _height, float _div);
	void axis(float _width, float _height, float _size);
	void axis(float _width, float _height, float _size, const sGColor& _color);
	void triangle(const sGVertex* _obj);
	void triangle(const sGVertex& _v1, const sGVertex& _v2, const sGVertex& _v3);
	void triangle(GLint _index, GLsizei _count);
	void triangle2(const void* _indices, GLsizei _count);
	void sinus(float _max, float _phase, float _size, float _range, float _linesize, float _psize);
	void gaussian2D(int _xSize, int _ySize, float _sigma, float _psize);
	void gaussian2D2(int _xSize, int _ySize, float _sigma, float _psize);
	void heatMap(GFunction& _func, float _psize);
	void heatMap2(GFunction& _func, float _psize);
	void heatMap(float _v, float _vmin, float _vmax, float& _r, float& _g, float& _b);
	sGColor heatMap(float _v, float _vmin, float _vmax, const sGColor& _color);
	void ecg(const float* _data, int _offset, int _size, float _linesize);
	void ecg(const float* _data, int _offset, int _size, float _yoffset, float _scale, float _linesize);
	void mcml(GFunction& _func, float _pointsize, float _alpha);
	void slice(GFunction& _func, int _xsize, int _ysize, int _zsize, int _xslice, int _yslice, int _zslice, float _pointsize);
	void position(float _alpha, float _beta, float _zoom);
	void camera(float _fovY, float _front, float _back, int width, int height);
	glm::mat4 camera(const sGCamera& _cam);
	void origin(float _linesize, float _transparency);
	void depthOn();
	void depthOff();
	void shader(const std::string& _vertexCode, const std::string& _fragmentCode);
	void shader2(const std::string& _vertexFile, const std::string& _fragmentFile);
	void shader3(const std::string& _shaderFile, GLenum _shaderType);
	void shader4(const std::string& _shaderFile, GLenum _shaderType);
	void pipeline(const GOpenGL& _vertex, const GOpenGL& _fragment);
	void pipeline();
	void attributs();
	void attribut(GLuint _location, GLint _size, GLuint _offset);
	const char* type(GLenum _type);
	void texture(GLenum _texture);
	void texture(const std::string& _image);
	void texture(GLubyte* _data, int _width, int _height);
	void texture2(const std::string& _image);
	void texture3(const std::string& _image);
	void texture4(const std::string& _image);
	void texture5(const std::string& _image);
	void compile(GLuint _shaderId, const std::string& _code);
	void use();
	void use(GLuint _programID);
	void fragment(GLuint _location, const char* _name);
	void vao(GLuint _vao);
	void vao(GLsizei _n, GLuint* _vao);
	void vbo(GLuint _vbo);
	void vbo(GLsizei _n, GLuint* _vbo);
	void vbo(GLuint _vbo, const void* _data, GLsizeiptr _size);
	void vbo(GLuint _vbo, const char* _name);
	void vbo(GLuint _vbo, GLuint& _attrib, const char* _name);
	void vbo(GLuint _location, GLint _size, GLsizei _stride, GLuint _pointer);
	void vbo2(GLuint _location, GLuint _vbo, GLintptr _offset, GLsizei _stride);
	void vbo2(GLuint _ebo, const void* _data, GLsizeiptr _size);
	void deleteVao(GLsizei _n, GLuint* _vao);
	void deleteVbo(GLsizei _n, GLuint* _vbo);
	void disableAttrib(GLuint _attrib);
	void deleteProgram();
	void deleteTexture();
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
	void angle(bool _animate, float& _angle);
	void rotation(glm::mat4& _rotation, float _angle);
	void debug();
	void debug2();
	static void APIENTRY onDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* param);

private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;
	std::string m_title;
	float m_ratio;
	GLuint m_programID;
	GLuint m_textureID;
	GLuint m_pipelineID;
	GLubyte* m_blockBuffer;
	GLint m_blockSize;
	GLuint* m_indices;
	GLint* m_offset;
};
//==============================================
#endif
//==============================================
