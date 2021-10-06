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
    void onKey(GLFWkeyfun _func);
    void onKey(int action, int key, bool& _freeze, float& _alpha, float& _beta, float& _zoom);
    void onResize(GLFWframebuffersizefun _func);
    void onMouse(GLFWmousebuttonfun _func);
    void onCursor(GLFWcursorposfun _func);
    void onScroll(GLFWscrollfun _func);
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
    void heatMap(GFunction& _func, float _psize);
    void heatMap(float _v, float _vmin, float _vmax, float& _r, float& _g, float& _b);
    void ecg(const float* _data, int _offset, int _size, float _linesize);
    void ecg(const float* _data, int _offset, int _size, float _yoffset, float _scale, float _linesize);
    void position(float _alpha, float _beta, float _zoom);
    void camera(float _fovY, float _front, float _back, int width, int height);

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;
    float m_ratio;
};
//==============================================
#endif
//==============================================
