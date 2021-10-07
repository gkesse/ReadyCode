//===============================================
#include "GOpenGL.h"
#include "GFunction.h"
#include "GFile.h"
//===============================================
GOpenGL::GOpenGL() {
    m_window = 0;
    m_width = 400;
    m_height = 400;
    m_title = "ReadyApp";
    m_ratio = 0.f;
    m_program = 0;
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
    glEnable(GL_ALPHA_TEST) ;
}
//===============================================
void GOpenGL::init2() {
    glfwInit();
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    glewExperimental = true;
    glewInit();
}
//===============================================
void GOpenGL::bgcolor() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
//===============================================
void GOpenGL::shader(const std::string& _vertex, const std::string& _fragment) {
    GFile lFile;

    lFile.filename(_vertex);
    std::string lVertexCode = lFile.read();
    GLuint lVertexId = glCreateShader(GL_VERTEX_SHADER);
    compile(lVertexId, lVertexCode);

    lFile.filename(_fragment);
    std::string lFragmentCode = lFile.read();
    GLuint lFragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    compile(lFragmentId, lFragmentCode);

    m_program = glCreateProgram();

    glAttachShader(m_program, lVertexId);
    glAttachShader(m_program, lFragmentId);
    glLinkProgram(m_program);

    GLint lResult = 0;
    int lLength;

    glGetProgramiv(m_program, GL_LINK_STATUS, &lResult);
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &lLength);

    glDeleteShader(lVertexId);
    glDeleteShader(lFragmentId);
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
    glUseProgram(m_program);
}
//===============================================
void GOpenGL::fragment(GLuint _location, const char* _name) {
    glBindFragDataLocation(m_program, _location, _name);
}
//===============================================
void GOpenGL::vao(GLsizei _n, GLuint* _vao) {
    glGenVertexArrays(_n, _vao);
    glBindVertexArray(*_vao);
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
    GLint lLocation = glGetAttribLocation(m_program, _name);
    glEnableVertexAttribArray(lLocation);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(lLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}
//===============================================
void GOpenGL::vbo(GLuint _vbo, GLuint& _attrib, const char* _name) {
	_attrib = glGetAttribLocation(m_program, _name);
    glEnableVertexAttribArray(_attrib);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(_attrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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
    glDeleteProgram(m_program);
}
//===============================================
void GOpenGL::onKey(GLFWkeyfun _func) {
    glfwSetKeyCallback(m_window, _func);
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
void GOpenGL::onResize(GLFWframebuffersizefun _func) {
    glfwSetFramebufferSizeCallback(m_window, _func);
    _func(m_window, m_width, m_height);
}
//===============================================
void GOpenGL::onMouse(GLFWmousebuttonfun _func) {
    glfwSetMouseButtonCallback(m_window, _func);
}
//===============================================
void GOpenGL::onMouse(int _button, int _action, bool& lock) {
    if (_button != GLFW_MOUSE_BUTTON_LEFT) {return;}
    if (_action == GLFW_PRESS) {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        lock = true;
    }
    else {
        lock = false;
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
//===============================================
void GOpenGL::onCursor(GLFWcursorposfun _func) {
    glfwSetCursorPosCallback(m_window, _func);
}
//===============================================
void GOpenGL::onCursor(double _x, double _y, bool& _lock, float& _alpha, float& _beta, int _cursorX, int& _cursorY) {
    if (_lock) {
        _alpha += (float) (_x - _cursorX) / 10.0f;
        _beta += (float) (_y - _cursorY) / 10.0f;
    }
    _cursorX = (int) _x;
    _cursorY = (int) _y;
}
//===============================================
void GOpenGL::onScroll(GLFWscrollfun _func) {
    glfwSetScrollCallback(m_window, _func);
}
//===============================================
void GOpenGL::onScroll(double _x, double _y, float& _zoom) {
    _zoom += (float) _y / 4.0f;
    if (_zoom < 0.0f) {
        _zoom = 0.0f;
    }
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
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    m_ratio = (float)m_width / (float)m_height;
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-m_ratio, m_ratio, -1.0f, 1.0f, 1.0f, -1.0f);
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
void GOpenGL::point(GFunction& _func, float _psize) {
    for(int i = 0; i < _func.size(); i++) {
        GLfloat x = _func.data()[i].x;
        GLfloat y = _func.data()[i].y;
        sGVertex v = {x, y, 0.0f, 1.0, 1.0, 1.0, 0.7f};
        point(v, _psize);
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
void GOpenGL::line(GFunction& _func, float _linesize) {
    for(int i = 0; i < _func.size() - 1; i++) {
        GLfloat x1 = _func.data()[i].x;
        GLfloat y1 = _func.data()[i].y;
        GLfloat x2 = _func.data()[i + 1].x;
        GLfloat y2 = _func.data()[i + 1].y;

        sGVertex v1 = {x1, y1, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f};
        sGVertex v2 = {x2, y2, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f};
        line(v1, v2, _linesize);
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
void GOpenGL::sinus(float _max, float _phase, float _size, float _range, float _linesize, float _psize) {
    GFunction lFunction;
    lFunction.sinus(_max, _phase, _size, _range);
    point(lFunction, _psize);
    line(lFunction, _linesize);
}
//===============================================
void GOpenGL::gaussian2D(int _xSize, int _ySize, float _sigma, float _psize) {
    GFunction lFunction;
    lFunction.gaussian2D(_xSize, _ySize, _sigma);
    heatMap(lFunction, _psize);
}
//===============================================
void GOpenGL::gaussian2D2(int _xSize, int _ySize, float _sigma, float _psize) {
    GFunction lFunction;
    lFunction.gaussian2D(_xSize, _ySize, _sigma);
    heatMap2(lFunction, _psize);
}
//===============================================
void GOpenGL::heatMap(GFunction& _func, float _psize) {
    float zMin, zMax;
    _func.zMinMax(zMin, zMax);

    glPointSize(_psize);
    glBegin(GL_POINTS);

    for(int i = 0; i < _func.size(); i++){
        const sGData d = _func.data()[i];
        float r, g, b;
        heatMap(d.z, zMin, zMax, r, g, b);
        glColor4f(r, g, b, 0.5f);
        glVertex3f(d.x, d.y, 0.f);
    }

    glEnd();
}
//===============================================
void GOpenGL::heatMap2(GFunction& _func, float _psize) {
    float zMin, zMax;
    _func.zMinMax(zMin, zMax);

    glPointSize(_psize);
    glBegin(GL_POINTS);

    for(int i = 0; i < _func.size(); i++){
        const sGData d = _func.data()[i];
        float r, g, b;
        heatMap(d.z, zMin, zMax, r, g, b);
        glColor4f(r, g, b, 0.5f);
        glVertex3f(d.x, d.y, d.z);
    }

    glEnd();
}
//===============================================
void GOpenGL::heatMap(float _v, float _vmin, float _vmax, float& _r, float& _g, float& _b) {
    float _half = (_vmin + _vmax) / 2;
    _b = 1.0f - _v/_half;
    _r = _v/_half - 1.0f;
    if(_b < 0) {_b = 0.f;}
    if(_r < 0) {_r = 0.f;}
    _g = 1.0f - _b - _r;
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
void GOpenGL::ecg(const float* _data, int _offset, int _size, float _linesize) {
    ecg(_data, _offset, _size, -0.5f, 0.1f, _linesize);
    ecg(_data, _offset + _size, _size, 0.0f, 0.5f, _linesize);
    ecg(_data, _offset + _size*2, _size, 0.5f, -0.25f, _linesize);
}
//===============================================
void GOpenGL::ecg(const float* _data, int _offset, int _size, float _yoffset, float _scale, float _linesize) {
    const float lSpace = 2.0f / _size * m_ratio;
    float lPos = -_size * lSpace / 2.0f;
    glLineWidth(_linesize);

    glBegin(GL_LINE_STRIP);
    glColor4f(0.1f, 1.0f, 0.1f, 0.8f);

    for(int i = _offset; i < _size + _offset; i++){
        const float data = _scale * _data[i] + _yoffset;
        glVertex3f(lPos, data, 0.0f);
        lPos += lSpace;
    }

    glEnd();
}
//===============================================
void GOpenGL::mcml(GFunction& _func, float _pointsize, float _alpha) {
    glPointSize(_pointsize);
    glBegin(GL_POINTS);
    for(int z = 0; z < _func.zsize(); z++){
        for(int x = 0; x < _func.xsize(); x++){
            for(int y = 0; y < _func.ysize(); y++){
                glColor4f(_func.vertex3D()[x][y][z].r, _func.vertex3D()[x][y][z].g, _func.vertex3D()[x][y][z].b, _alpha);
                glVertex3f(_func.vertex3D()[x][y][z].x, _func.vertex3D()[x][y][z].y, _func.vertex3D()[x][y][z].z);
            }
        }
    }
    glEnd();
}
//===============================================
void GOpenGL::slice(GFunction& _func, int _xsize, int _ysize, int _zsize, int _xslice, int _yslice, int _zslice, float _pointsize) {
    glPointSize(_pointsize);
    glBegin(GL_POINTS);
    // xy
    for(int x=0; x < _xsize; x++){
        for(int y=0; y < _ysize; y++){
            int z = _zslice;
            glColor4f(_func.vertex3D()[x][y][z].r,_func.vertex3D()[x][y][z].g,_func.vertex3D()[x][y][z].b, 0.9f);
            glVertex3f(_func.vertex3D()[x][y][z].x, _func.vertex3D()[x][y][z].y, _func.vertex3D()[x][y][z].z);
        }
    }
    // yz
    for(int z = 0; z < _zsize; z++){
        for(int y = 0; y < _ysize; y++){
            int x = _xslice;
            glColor4f(_func.vertex3D()[x][y][z].r,_func.vertex3D()[x][y][z].g,_func.vertex3D()[x][y][z].b, 0.9f);
            glVertex3f(_func.vertex3D()[x][y][z].x, _func.vertex3D()[x][y][z].y, _func.vertex3D()[x][y][z].z);
        }
    }
    // xz
    for(int z = 0; z < _zsize; z++){
        for(int x = 0; x < _xsize; x++){
            int y = _yslice;
            glColor4f(_func.vertex3D()[x][y][z].r,_func.vertex3D()[x][y][z].g,_func.vertex3D()[x][y][z].b, 0.9f);
            glVertex3f(_func.vertex3D()[x][y][z].x, _func.vertex3D()[x][y][z].y, _func.vertex3D()[x][y][z].z);
        }
    }
    glEnd();
}
//===============================================
void GOpenGL::position(float _alpha, float _beta, float _zoom) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -_zoom);
    glRotatef(_beta, 1.0, 0.0, 0.0);
    glRotatef(_alpha, 0.0, 0.0, 1.0);
}
//===============================================
void GOpenGL::camera(float _fovY, float _front, float _back, int width, int height) {
    const double DEG2RAD = 3.14159265 / 180;
    m_ratio = 1.0f; m_width = width; m_height = height;
    if(m_height > 0) {m_ratio = (float) m_width / (float) m_height;}
    glViewport(0, 0, m_width, m_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float lTangent = tan(_fovY / 2 * DEG2RAD);
    float lHeightF = _front * lTangent;
    float lWidthF = lHeightF * m_ratio;
    glFrustum(-lWidthF, lWidthF, -lHeightF, lHeightF, _front, _back);
}
//===============================================
void GOpenGL::origin(float _linesize, float _transparency) {
    glLineWidth(_linesize);
    glBegin(GL_LINES);
    // x-axis
    glColor4f(1.0f, 0.0f, 0.0f, _transparency);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor4f(1.0f, 0.0f, 0.0f, _transparency);
    glVertex3f(0.3f, 0.0f, 0.0f);
    // y-axis
    glColor4f(0.0f, 1.0f, 0.0f, _transparency);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor4f(0.0f, 1.0f, 0.0f, _transparency);
    glVertex3f(0.0f, 0.0f, 0.3f);
    // z-axis
    glColor4f(0.0f, 0.0f, 1.0f, _transparency);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor4f(0.0f, 0.0f, 1.0f, _transparency);
    glVertex3f(0.0f, 0.3f, 0.0f);
    glEnd();
}
//===============================================
void GOpenGL::depth(bool _on) {
    if(_on) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }
}
//===============================================
