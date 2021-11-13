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
    void glfw();
    void major(int _major);
    void minor(int _minor);
    void compatOn();
    void core();
    void window(int _width, int _height, const std::string& _title);
    void window(const sGWindow& _win);
    void context();
    void pointOn();
    void lineOn();
    void blendOn();
    void colorBuffer();
    void depthBuffer();
    void size(int& _width, int& _height);
    void size(sGWindow& _win);
    void ratio(sGWindow& _win);
    float ratio();
    void viewport(const sGWindow& _win);
    void projection();
    void ortho(const sGWindow& _win);
    void ortho(const sGGrid& _grid);
    void modelview();
    void gridXY(const sGGrid& _grid);
    void axisXY(const sGGrid& _grid);
    void origin(const sGGrid& _grid);
    void translate(const sGPoint& _p);
    void init();
    void init(int _argc, char** _argv);
    void init2();
    void init3();
    void bgcolor(const sGColor& _color);
    void onKey(GLFWkeyfun _func);
    void onKey();
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
    void onDisplay(void (*_func)(void));
    void coordinate(sGCamera& _cam, GLfloat _rho, GLfloat _theta, GLfloat _phi);
    void normal(GLfloat* _vertex, GLfloat* _normal, int& _ncircle, int& _nvertex, float _pointsize);
    void vector(GLfloat* _vertex, GLfloat* _normal, float _pointsize);
    void loop();
    bool isClose();
    void close();
    void pollEvents();
    void viewport2();
    void viewport(int _width, int _height);
    void point(const sGGrid& _grid, const sGPoint& _p);
    void point(const sGVertex& _v, float _pointsize);
    void point(const sGPoint& _v, const sGColor& _color, float _pointsize);
    void point(float _xmin, float _xmax, float _xstep, float _pointsize, const sGColor& _color);
    void point(sGPoint* _data, int _size, float _pointsize, const sGColor& _color);
    void line(const sGPoint& _v1, const sGPoint& _v2, const sGColor& _color, float _lineWidth);
    void line(const sGVertex& _v1, const sGVertex& _v2, float _linewidth);
    void line(const sGVertex* _vs, float _linewidth);
    void line(sGPoint* _data, int _size, float _linesize, const sGColor& _color);
    void axis(float _width, float _height, float _size);
    void axis(float _width, float _height, float _size, const sGColor& _color);
    void triangle(const sGVertex* _obj);
    void triangle(const sGVertex& _v1, const sGVertex& _v2, const sGVertex& _v3);
    void triangle(GLint _index, GLsizei _count);
    void triangle2(const void* _indices, GLsizei _count);
    void sinus(const sGSinus& _sinus);
    void gaussian2D(const sGGaussian2D& _gauss);
    void gaussian2D2(const sGGaussian2D& _gauss);
    void heatMap(sGPoint* _data, int _size, float _zmin, float _zmax, float _pointsize, float _alpha);
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
    void shader(const std::string& _vertex, const std::string& _fragment);
    void shader2(const std::string& _vertex, const std::string& _fragment);
    void texture(GLenum _texture);
    void texture(const std::string& _image);
    void texture(GLubyte* _data, int _width, int _height);
    void texture2(const std::string& _image);
    void texture3(const std::string& _image);
    void texture4(const std::string& _image);
    void texture5(const std::string& _image);
    void compile(GLuint _shaderId, const std::string& _code);
    void use();
    void fragment(GLuint _location, const char* _name);
    void vao(GLuint _vao);
    void vao(GLsizei _n, GLuint* _vao);
    void vbo(GLuint _vbo);
    void vbo(GLsizei _n, GLuint* _vbo);
    void vbo(GLuint _vbo, const void* _data, GLsizeiptr _size);
    void vbo2(GLuint _ebo, const void* _data, GLsizeiptr _size);
    void vbo(GLuint _vbo, const char* _name);
    void vbo(GLuint _vbo, GLuint& _attrib, const char* _name);
    void vbo(GLuint _location, GLint _size, GLsizei _stride, GLuint _pointer);
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
    void uniform2(const char* _name, GLuint _v0);

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;
    float m_ratio;
    GLuint m_program;
    GLuint m_texture;
};
//==============================================
#endif
//==============================================
