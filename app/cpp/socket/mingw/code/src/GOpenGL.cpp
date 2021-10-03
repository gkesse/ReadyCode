//===============================================
#define NK_IMPLEMENTATION
//===============================================
#include "GOpenGL.h"
#include "GFunction.h"
//===============================================
GOpenGL::GOpenGL() {
    m_window = 0;
    m_width = 400;
    m_height = 400;
    m_title = "ReadyApp";
}
//===============================================
GOpenGL::~GOpenGL() {

}
//===============================================
void GOpenGL::width(int _width) {
    m_width = _width;
}
//===============================================
void GOpenGL::height(int _height) {
    m_height = _height;
}
//===============================================
void GOpenGL::title(const std::string& _title) {
    m_title = _title;
}
//===============================================
void GOpenGL::init() {
    glfwInit();
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
void GOpenGL::viewport() {
    float lRatio;
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    lRatio = (float)m_width / (float)m_height;
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-lRatio, lRatio, -1.0f, 1.0f, 1.0f, -1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//===============================================
void GOpenGL::point(const sGVertex& _obj, int _width) {
    glPointSize(_width);
    glBegin(GL_POINTS);
    glColor4f(_obj.r, _obj.g, _obj.b, _obj.a);
    glVertex3f(_obj.x, _obj.y, _obj.z);
    glEnd();
}
//===============================================
void GOpenGL::point() {
    GLfloat size = 5.0f;
    for(GLfloat x = 0.0f; x <= 1.0f; x += 0.2f, size += 5.0f){
        sGVertex lPoint = {x, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        point(lPoint, size);
    }
}
//===============================================
void GOpenGL::line(const sGVertex* _obj, int _width) {
    glLineWidth(_width);
    glBegin(GL_LINES);
    for(int i = 0; i < 2; i++) {
        sGVertex lObj = _obj[i];
        glColor4f(lObj.r, lObj.g, lObj.b, lObj.a);
        glVertex3f(lObj.x, lObj.y, lObj.z);
    }
    glEnd();
}
//===============================================
void GOpenGL::line(const sGVertex& _v1, const sGVertex& _v2, int _width) {
    sGVertex lLine[] = {_v1, _v2};
    line(lLine, _width);
}
//===============================================
void GOpenGL::line(sGData* _data, int _size) {
    for(int i = 0; i < _size - 1; i++) {
        GLfloat x1 = _data[i].x;
        GLfloat y1 = _data[i].y;
        GLfloat x2 = _data[i + 1].x;
        GLfloat y2 = _data[i + 1].y;

        sGVertex v1 = {x1, y1, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f};
        sGVertex v2 = {x2, y2, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f};
        line(v1, v2, 4.0f);
    }
}
//===============================================
void GOpenGL::grid(float _width, float _height, float _div) {
    // horizontal
    for(float i = -_height; i < _height; i += _div){
        sGVertex v1 = {-_width, i, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        sGVertex v2 = {_width, i, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        line(v1, v2, 1.f);
    }
    // vertical
    for(float i = -_width; i < _width; i += _div){
        sGVertex v1 = {i, -_height, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        sGVertex v2 = {i, _height, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        line(v1, v2, 1.f);
    }
}
//===============================================
void GOpenGL::axis(float _width, float _height, float _size) {
    sGVertex v1 = {-_width, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.7f};
    sGVertex v2 = {_width, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.7f};
    sGVertex v3 = {0.0f, _height, 0.0f, 0.0f, 0.0f, 1.0f, 0.7f};
    sGVertex v4 = {0.0f, -_height, 0.0f, 0.0f, 0.0f, 1.0f, 0.7f};
    line(v1, v2, _size);
    line(v3, v4, _size);
}
//===============================================
void GOpenGL::axis(float _width, float _height, float _size, const sGColor& _color) {
    sGVertex v1 = {-_width, 0.0f, 0.0f, _color.r, _color.g, _color.b, _color.a};
    sGVertex v2 = {_width, 0.0f, 0.0f, _color.r, _color.g, _color.b, _color.a};
    sGVertex v3 = {0.0f, _height, 0.0f, _color.r, _color.g, _color.b, _color.a};
    sGVertex v4 = {0.0f, -_height, 0.0f, _color.r, _color.g, _color.b, _color.a};
    line(v1, v2, _size);
    line(v3, v4, _size);
}
//===============================================
void GOpenGL::triangle(const sGVertex* _obj) {
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < 3; i++) {
        sGVertex lObj = _obj[i];
        glColor4f(lObj.r, lObj.g, lObj.b, lObj.a);
        glVertex3f(lObj.x, lObj.y, lObj.z);
    }
    glEnd();
}
//===============================================
void GOpenGL::triangle(const sGVertex& _v1, const sGVertex& _v2, const sGVertex& _v3) {
    sGVertex lTriangle[] = {_v1, _v2, _v3};
    triangle(lTriangle);
}
//===============================================
void GOpenGL::sinus(float _max, float _phase, float _size, float _range) {
    GFunction lFunction;
    sGData* lData = lFunction.sinus(_max, _phase, _size, _range);
    line(lData, _size);
    delete lData;
}
//===============================================
void GOpenGL::gaussian2D(int _xSize, int _ySize, float _sigma, float _psize) {
    GFunction lFunction;
    lFunction.gaussian2D(_xSize, _ySize, _sigma);
    heatMap(lFunction, _psize);
}
//===============================================
void GOpenGL::heatMap(GFunction& _func, float _psize) {
    float zMin, zMax;
    _func.zMinMax(zMin, zMax);
    const float zHalf = (zMax + zMin) / 2;

    glPointSize(_psize);
    glBegin(GL_POINTS);

    for(int i = 0; i < _func.size(); i++){
        const sGData d = _func.data()[i];
        float zValue = d.z;
        float b = 1.0f - zValue/zHalf;
        float r = zValue/zHalf - 1.0f;
        if(b < 0) {b = 0;}
        if(r < 0) {r = 0;}
        float g = 1.0f - b - r;

        glColor4f(r, g, b, 0.5f);
        glVertex3f(d.x, d.y, 0.0f);
    }

    glEnd();
}
//===============================================
