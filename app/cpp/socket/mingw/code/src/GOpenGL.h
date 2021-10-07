//===============================================
#ifndef _GOpenGL_
#define _GOpenGL_
//===============================================
#include "GInclude.h"
#include "GFunction.h"
//===============================================
class GOpenGL {
public:
	GOpenGL();
	~GOpenGL();
	void width(int _width);
	void height(int _height);
	void title(const std::string& _title);
	void init();
	void init2();
	void bgcolor();
	void onKey(GLFWkeyfun _func);
	void onKey(int action, int key, bool& _freeze, float& _alpha, float& _beta, float& _zoom);
	void onKey2(int action, int key, int _xsize, int _ysize, int _zsize, float& _pointsize, int& _xslice, int& _yslice, int& _zslice, float& _zoom);
	void onResize(GLFWframebuffersizefun _func);
	void onMouse(GLFWmousebuttonfun _func);
	void onMouse(int _button, int _action, bool& lock);
	void onCursor(GLFWcursorposfun _func);
	void onCursor(double _x, double _y, bool& _lock, float& _alpha, float& _beta, int _cursorX, int& _cursorY);
	void onScroll(GLFWscrollfun _func);
	void onScroll(double _x, double _y, float& _zoom);
	bool isClose();
	void close();
	void pollEvents();
	void viewport();
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
	void origin(float _linesize, float _transparency);
	void depth(bool _on);
	void shader(const std::string& _vertex, const std::string& _fragment);
	void compile(GLuint _shaderId, const std::string& _code);
	void use();
	void fragment(GLuint _location, const char* _name);
	void vao(GLsizei _n, GLuint* _vao);
	void vbo(GLsizei _n, GLuint* _vbo);
	void vbo(GLuint _vbo, const void* _data, GLsizeiptr _size);
	void vbo(GLuint _vbo, const char* _name);
	void vbo(GLuint _vbo, GLuint& _attrib, const char* _name);
	void deleteVao(GLsizei _n, GLuint* _vao);
	void deleteVbo(GLsizei _n, GLuint* _vbo);
	void disableAttrib(GLuint _attrib);
	void deleteProgram();

private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;
	std::string m_title;
	float m_ratio;
	GLuint m_program;
};
//==============================================
#endif
//==============================================
