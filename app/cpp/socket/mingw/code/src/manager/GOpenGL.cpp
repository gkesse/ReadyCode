//===============================================
#define STB_IMAGE_IMPLEMENTATION
//===============================================
#include "GOpenGL.h"
#include "GFunction.h"
#include "GFile.h"
#include "GLine.h"
//===============================================
#include <stb_image.h>
//===============================================
GOpenGL::GOpenGL() {
    m_window = 0;
    m_width = 400;
    m_height = 400;
    m_title = "ReadyApp";
    m_ratio = 0.f;
    m_program = -1;
    m_texture = -1;
}
//===============================================
GOpenGL::~GOpenGL() {

}
//===============================================
void GOpenGL::glfw() {
    glfwInit();
}
//===============================================
void GOpenGL::major(int _major) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _major);
}
//===============================================
void GOpenGL::minor(int _minor) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _minor);
}
//===============================================
void GOpenGL::compatOn() {
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}
//===============================================
void GOpenGL::core() {
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
//===============================================
void GOpenGL::window(int _width, int _height, const std::string& _title) {
    m_window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
}
//===============================================
void GOpenGL::window(const sGWindow& _win) {
    m_window = glfwCreateWindow(_win.width, _win.height, _win.title.c_str(), NULL, NULL);
}
//===============================================
void GOpenGL::context() {
    glfwMakeContextCurrent(m_window);
}
//===============================================
void GOpenGL::pointOn() {
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}
//===============================================
void GOpenGL::lineOn() {
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}
//===============================================
void GOpenGL::blendOn() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
//===============================================
void GOpenGL::colorBuffer() {
    glClear(GL_COLOR_BUFFER_BIT);
}
//===============================================
void GOpenGL::depthBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//===============================================
void GOpenGL::size(int& _width, int& _height) {
    glfwGetFramebufferSize(m_window, &_width, &_height);
}
//===============================================
void GOpenGL::size(sGWindow& _win) {
    glfwGetFramebufferSize(m_window, &_win.width, &_win.height);
}
//===============================================
void GOpenGL::ratio(sGWindow& _win) {
    _win.ratio = (float)_win.width / _win.height;
}
//===============================================
float GOpenGL::ratio() {
    int lWidth, lHeight;
    glfwGetFramebufferSize(m_window, &lWidth, &lHeight);
    float lRatio = (float)lWidth / lHeight;
    return lRatio;
}
//===============================================
void GOpenGL::viewport(const sGWindow& _win) {
    glViewport(0, 0, _win.width, _win.height);
}
//===============================================
void GOpenGL::projection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}
//===============================================
void GOpenGL::ortho(const sGWindow& _win) {
    glOrtho(-_win.ratio, _win.ratio, -1.f, 1.f, 1.f, -1.f);
}
//===============================================
void GOpenGL::ortho(const sGGrid& _grid) {
    glOrtho(
        _grid.xrange.m_min,
        _grid.xrange.m_max,
           _grid.yrange.m_min,
        _grid.yrange.m_max,
        _grid.zrange.m_max,
        _grid.zrange.m_min
    );
}
//===============================================
void GOpenGL::modelview() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//===============================================
void GOpenGL::gridXY(const sGGrid& _grid) {
    sGRange xRange = {-_grid.width, _grid.width};
    sGRange yRange = {-_grid.height, _grid.height};
    xRange -= _grid.origin.x * _grid.gridDiv.x;
    yRange -= _grid.origin.y * _grid.gridDiv.y;
    // horizontal
    for(float i = yRange.m_min; i < yRange.m_max; i += _grid.gridDiv.y) {
        sGPoint v1 = {xRange.m_min, i, 0.f};
        sGPoint v2 = {xRange.m_max, i, 0.f};
        line(v1, v2, _grid.gridColor, _grid.gridWidth);
    }
    // vertical
    for(float i = xRange.m_min; i < xRange.m_max; i += _grid.gridDiv.y) {
        sGPoint v1 = {i, yRange.m_min, 0.f};
        sGPoint v2 = {i, yRange.m_max, 0.f};
        line(v1, v2, _grid.gridColor, _grid.gridWidth);
    }
}
//===============================================
void GOpenGL::axisXY(const sGGrid& _grid) {
    sGRange xRange = {-_grid.width, _grid.width};
    sGRange yRange = {-_grid.height, _grid.height};
    xRange -= _grid.origin.x * _grid.gridDiv.x;
    yRange -= _grid.origin.y * _grid.gridDiv.y;
    sGPoint v1 = {xRange.m_min, 0.f, 0.f};
    sGPoint v2 = {xRange.m_max, 0.f, 0.f};
    sGPoint v3 = {0.f, yRange.m_min, 0.f};
    sGPoint v4 = {0.f, yRange.m_max, 0.f};
    line(v1, v2,  _grid.axisColor, _grid.axisWidth);
    line(v3, v4,  _grid.axisColor, _grid.axisWidth);
}
//===============================================
void GOpenGL::origin(const sGGrid& _grid) {
    sGPoint lOrigin = _grid.origin * _grid.gridDiv;
    translate(lOrigin);
}
//===============================================
void GOpenGL::translate(const sGPoint& _p) {
    glTranslatef(_p.x, _p.y, _p.z);
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
    glEnable(GL_ALPHA_TEST);
}
//===============================================
void GOpenGL::init(int _argc, char** _argv) {
    glutInit(&_argc, _argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(m_width, m_height);
    glutCreateWindow(m_title.c_str());
}
//===============================================
void GOpenGL::init2() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    glewExperimental = true;
    glewInit();
}
//===============================================
void GOpenGL::bgcolor(const sGColor& _color) {
    glClearColor(_color.r, _color.g, _color.b, _color.a);
}
//===============================================
void GOpenGL::shader(const std::string& _vertex, const std::string& _fragment) {
    GLuint lVertexId = glCreateShader(GL_VERTEX_SHADER);
    compile(lVertexId, _vertex);

    GLuint lFragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    compile(lFragmentId, _fragment);

    m_program = glCreateProgram();

    glAttachShader(m_program, lVertexId);
    glAttachShader(m_program, lFragmentId);
    glLinkProgram(m_program);

    GLint lResult = 0;
    int logLength;

    glGetProgramiv(m_program, GL_LINK_STATUS, &lResult);
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);

    glDeleteShader(lVertexId);
    glDeleteShader(lFragmentId);
}
//===============================================
void GOpenGL::shader2(const std::string& _vertex, const std::string& _fragment) {
    GFile lFile;
    lFile.filename(_vertex);
    std::string lVertexCode = lFile.read();
    lFile.filename(_fragment);
    std::string lFragmentCode = lFile.read();
    shader(lVertexCode, lFragmentCode);
}
//===============================================
void GOpenGL::texture(GLenum _texture) {
    glActiveTexture(_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
//===============================================
void GOpenGL::texture(const std::string& _image) {
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
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
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA, _width, _height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, _data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
//===============================================
void GOpenGL::texture2(const std::string& _image) {
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
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
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
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
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
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
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
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
void GOpenGL::use() {
    glUseProgram(m_program);
}
//===============================================
void GOpenGL::fragment(GLuint _location, const char* _name) {
    glBindFragDataLocation(m_program, _location, _name);
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
void GOpenGL::vbo2(GLuint _ebo, const void* _data, GLsizeiptr _size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size, _data, GL_STATIC_DRAW);
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
void GOpenGL::vbo(GLuint _location, GLint _size, GLsizei _stride, GLuint _pointer) {
    glVertexAttribPointer(_location, _size, GL_FLOAT, GL_FALSE, _stride * sizeof(GLfloat), (void*)(_pointer * sizeof(GLfloat)));
    glEnableVertexAttribArray(_location);
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
    m_program = -1;
}
//===============================================
void GOpenGL::deleteTexture() {
    glDeleteTextures(1, &m_texture);
    m_texture = -1;
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
void GOpenGL::onKey(GLfloat& _mixValue) {
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, true);
    }

    if(glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS) {
        _mixValue += 0.01f;
        if(_mixValue >= 1.f) {
            _mixValue = 1.f;
        }
    }

    if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        _mixValue -= 0.01f;
        if (_mixValue <= 0.f) {
            _mixValue = 0.f;
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
        _alpha += 5.f;
        break;
    case GLFW_KEY_RIGHT:
        _alpha -= 5.f;
        break;
    case GLFW_KEY_UP:
        _beta -= 5.f;
        break;
    case GLFW_KEY_DOWN:
        _beta += 5.f;
        break;
    case GLFW_KEY_PAGE_UP:
        _zoom -= 0.25f;
        if (_zoom < 0.f) {_zoom = 0.f;}
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
        if (_zoom < 0.f) {_zoom = 0.f;}
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
        _alpha += (float) (_x - _cursorX) / 10.f;
        _beta += (float) (_y - _cursorY) / 10.f;
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
    _zoom += (float) _y / 4.f;
    if (_zoom < 0.f) {
        _zoom = 0.f;
    }
}
//===============================================
void GOpenGL::onDisplay(void (*_func)(void)) {
    glutDisplayFunc(_func);
}
//===============================================
void GOpenGL::coordinate(sGCamera& _cam, GLfloat _rho, GLfloat _theta, GLfloat _phi) {
    _cam.eye[0] = _rho*sin(90.0 - _theta)*sin(_phi);
    _cam.eye[1] = _rho*cos(90.0 - _theta);
    _cam.eye[2] = _rho*sin(90.0 - _theta)*cos(_phi);
}
//===============================================
void GOpenGL::normal(GLfloat* _vertex, GLfloat* _normal, int& _ncircle, int& _nvertex, float _pointsize) {
    int lSize = _ncircle*_nvertex;
    GLfloat* lVertex = _vertex;
    GLfloat* lNormal = _vertex;
    for(int i = 0; i < lSize; i++) {
        vector(lVertex, lNormal, _pointsize);
        lVertex += 3;
        lNormal += 3;
    }

}
//===============================================
void GOpenGL::vector(GLfloat* _vertex, GLfloat* _normal, float _pointsize) {
    glPointSize(_pointsize);
    glBegin(GL_LINES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(_vertex[0], _vertex[1], _vertex[2]);
    glColor3f(0.f, 1.f, 1.f);
    glVertex3f(_vertex[0] + _normal[0], _vertex[1] + _normal[1], _vertex[2] + _normal[2]);
    glEnd();
}
//===============================================
void GOpenGL::loop() {
    glutMainLoop();
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
void GOpenGL::viewport2() {
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    m_ratio = (float)m_width / (float)m_height;
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-m_ratio, m_ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//===============================================
void GOpenGL::viewport(int _width, int _height) {
    glViewport(0, 0, _width, _height);
}
//===============================================
void GOpenGL::point(const sGGrid& _grid, const sGPoint& _p) {
    sGPoint p = (_p * _grid.gridDiv) / _grid.axisDiv;
    point(p, _grid.pointColor, _grid.pointsize);
}
//===============================================
void GOpenGL::point(const sGVertex& _v, float _pointsize) {
    glPointSize(_pointsize);
    glBegin(GL_POINTS);
    glColor4f(_v.c.r, _v.c.g, _v.c.b, _v.c.a);
    glVertex3f(_v.d.x, _v.d.y, _v.d.z);
    glEnd();
}
//===============================================
void GOpenGL::point(const sGPoint& _v, const sGColor& _color, float _pointsize) {
    glPointSize(_pointsize);
    glBegin(GL_POINTS);
    glColor4f(_color.r, _color.g, _color.b, _color.a);
    glVertex3f(_v.x, _v.y, _v.z);
    glEnd();
}
//===============================================
void GOpenGL::point(float _xmin, float _xmax, float _xstep, float _pointsize, const sGColor& _color) {
    GLfloat lPointSize = 5.f;
    for(GLfloat x = _xmin; x <= _xmax; x += _xstep, lPointSize += _pointsize){
        sGVertex lPoint = {{x, 0.f, 0.f}, _color};
        point(lPoint, lPointSize);
    }
}
//===============================================
void GOpenGL::point(sGPoint* _data, int _size, float _pointsize, const sGColor& _color) {
    for(int i = 0; i < _size; i++) {
        GLfloat x = _data[i].x;
        GLfloat y = _data[i].y;
        sGVertex v = {{x, y, 0.f}, _color};
        point(v, _pointsize);
    }
}
//===============================================
void GOpenGL::line(const sGPoint& _v1, const sGPoint& _v2, const sGColor& _color, float _lineWidth) {
    glLineWidth(_lineWidth);
    glBegin(GL_LINES);
    glColor4f(_color.r, _color.g, _color.b, _color.a);
    glVertex3f(_v1.x, _v1.y, _v1.z);
    glColor4f(_color.r, _color.g, _color.b, _color.a);
    glVertex3f(_v2.x, _v2.y, _v2.z);
    glEnd();
}
//===============================================
void GOpenGL::line(const sGVertex& _v1, const sGVertex& _v2, float _lineWidth) {
    glLineWidth(_lineWidth);
    glBegin(GL_LINES);
    glColor4f(_v1.c.r, _v1.c.g, _v1.c.b, _v1.c.a);
    glVertex3f(_v1.d.x, _v1.d.y, _v1.d.z);
    glColor4f(_v2.c.r, _v2.c.g, _v2.c.b, _v2.c.a);
    glVertex3f(_v2.d.x, _v2.d.y, _v2.d.z);
    glEnd();
}
//===============================================
void GOpenGL::line(const sGVertex* _vs, float _linewidth) {
    glLineWidth(_linewidth);
    glBegin(GL_LINES);
    for(int i = 0; i < 2; i++) {
        sGVertex lV = _vs[i];
        glColor4f(lV.c.r, lV.c.g, lV.c.b, lV.c.a);
        glVertex3f(lV.d.x, lV.d.y, lV.d.z);
    }
    glEnd();
}
//===============================================
void GOpenGL::line(sGPoint* _data, int _size, float _linesize, const sGColor& _color) {
    for(int i = 0; i < _size - 1; i++) {
        GLfloat x1 = _data[i + 0].x;
        GLfloat y1 = _data[i + 0].y;
        GLfloat x2 = _data[i + 1].x;
        GLfloat y2 = _data[i + 1].y;

        sGVertex v1 = {{x1, y1, 0.f}, _color};
        sGVertex v2 = {{x2, y2, 0.f}, _color};
        line(v1, v2, _linesize);
    }
}
//===============================================
void GOpenGL::axis(float _width, float _height, float _size) {
    sGVertex v1 = {{-_width, 0.f, 0.f}, {1.f, 0.f, 0.f, 0.7f}};
    sGVertex v2 = {{_width, 0.f, 0.f}, {0.f, 1.f, 0.f, 0.7f}};
    sGVertex v3 = {{0.f, _height, 0.f}, {0.f, 0.f, 1.f, 0.7f}};
    sGVertex v4 = {{0.f, -_height, 0.f}, {0.f, 0.f, 1.f, 0.7f}};
    line(v1, v2, _size);
    line(v3, v4, _size);
}
//===============================================
void GOpenGL::axis(float _width, float _height, float _size, const sGColor& _color) {
    sGVertex v1 = {{-_width, 0.f, 0.f}, _color};
    sGVertex v2 = {{_width, 0.f, 0.f}, _color};
    sGVertex v3 = {{0.f, _height, 0.f}, _color};
    sGVertex v4 = {{0.f, -_height, 0.f}, _color};
    line(v1, v2, _size);
    line(v3, v4, _size);
}
//===============================================
void GOpenGL::triangle(const sGVertex* _vs) {
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < 3; i++) {
        sGVertex lV = _vs[i];
        glColor4f(lV.c.r, lV.c.g, lV.c.b, lV.c.a);
        glVertex3f(lV.d.x, lV.d.y, lV.d.z);
    }
    glEnd();
}
//===============================================
void GOpenGL::triangle(const sGVertex& _v1, const sGVertex& _v2, const sGVertex& _v3) {
    sGVertex lTriangle[] = {_v1, _v2, _v3};
    triangle(lTriangle);
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
void GOpenGL::sinus(const sGSinus& _sinus) {
    GFunction lFunction;
    lFunction.sinus(_sinus.max, _sinus.phase, _sinus.size, _sinus.range);
    point(lFunction.sinus(), _sinus.size, _sinus.pointsize, _sinus.pointcolor);
    line(lFunction.sinus(), _sinus.size, _sinus.linewidth, _sinus.linecolor);
}
//===============================================
void GOpenGL::gaussian2D(const sGGaussian2D& _gauss) {
    GFunction lFunction;
    lFunction.gaussian2D(_gauss.xsize, _gauss.ysize, _gauss.sigma);
    heatMap(lFunction.gaussian2D(), _gauss.size, _gauss.zmin, _gauss.zmax, _gauss.pointsize, _gauss.alpha);
}
//===============================================
void GOpenGL::gaussian2D2(const sGGaussian2D& _gauss) {
    GFunction lFunction;
    lFunction.gaussian2D(_gauss.xsize, _gauss.ysize, _gauss.sigma);
    heatMap(lFunction.gaussian2D(), _gauss.size, _gauss.zmin, _gauss.zmax, _gauss.pointsize, _gauss.alpha);
}
//===============================================
void GOpenGL::heatMap(sGPoint* _data, int _size, float _zmin, float _zmax, float _pointsize, float _alpha) {
    glPointSize(_pointsize);
    glBegin(GL_POINTS);

    for(int i = 0; i < _size; i++){
        const sGPoint d = _data[i];
        float r, g, b;
        heatMap(d.z, _zmin, _zmax, r, g, b);
        glColor4f(r, g, b, _alpha);
        glVertex3f(d.x, d.y, d.z);
    }

    glEnd();
}
//===============================================
void GOpenGL::heatMap(float _v, float _vmin, float _vmax, float& _r, float& _g, float& _b) {
    float _half = (_vmin + _vmax) / 2;
    _b = 1.f - _v/_half;
    _r = _v/_half - 1.f;
    if(_b < 0) {_b = 0.f;}
    if(_r < 0) {_r = 0.f;}
    _g = 1.f - _b - _r;
}
//===============================================
sGColor GOpenGL::heatMap(float _v, float _vmin, float _vmax, const sGColor& _color) {
    sGColor lColor = _color;
    float dv = _vmax - _vmin;
    if (_v < (_vmin + 0.25f * dv)) {
        lColor.r = 0.f;
        lColor.g = 4.f * (_v - _vmin) / dv;
    }
    else if (_v < (_vmin + 0.5f * dv)) {
        lColor.r = 0.f;
        lColor.b = 1.f + 4.f * (_vmin + 0.25f * dv - _v) / dv;
    }
    else if (_v < (_vmin + 0.75f * dv)) {
        lColor.r = 4.f * (_v - _vmin - 0.5f * dv) / dv;
        lColor.b = 0.f;
    }
    else {
        lColor.g = 1.f + 4.f * (_vmin + 0.75f * dv - _v) / dv;
        lColor.b = 0.f;
    }
    return lColor;
}
//===============================================
void GOpenGL::ecg(const float* _data, int _offset, int _size, float _linesize) {
    ecg(_data, _offset, _size, -0.5f, 0.1f, _linesize);
    ecg(_data, _offset + _size, _size, 0.f, 0.5f, _linesize);
    ecg(_data, _offset + _size*2, _size, 0.5f, -0.25f, _linesize);
}
//===============================================
void GOpenGL::ecg(const float* _data, int _offset, int _size, float _yoffset, float _scale, float _linesize) {
    const float lSpace = 2.f / _size * m_ratio;
    float lPos = -_size * lSpace / 2.f;
    glLineWidth(_linesize);

    glBegin(GL_LINE_STRIP);
    glColor4f(0.1f, 1.f, 0.1f, 0.8f);

    for(int i = _offset; i < _size + _offset; i++){
        const float data = _scale * _data[i] + _yoffset;
        glVertex3f(lPos, data, 0.f);
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
                glColor4f(_func.vertex3D()[x][y][z].c.r, _func.vertex3D()[x][y][z].c.g, _func.vertex3D()[x][y][z].c.b, _alpha);
                glVertex3f(_func.vertex3D()[x][y][z].d.x, _func.vertex3D()[x][y][z].d.y, _func.vertex3D()[x][y][z].d.z);
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
            glColor4f(_func.vertex3D()[x][y][z].c.r,_func.vertex3D()[x][y][z].c.g,_func.vertex3D()[x][y][z].c.b, 0.9f);
            glVertex3f(_func.vertex3D()[x][y][z].d.x, _func.vertex3D()[x][y][z].d.y, _func.vertex3D()[x][y][z].d.z);
        }
    }
    // yz
    for(int z = 0; z < _zsize; z++){
        for(int y = 0; y < _ysize; y++){
            int x = _xslice;
            glColor4f(_func.vertex3D()[x][y][z].c.r,_func.vertex3D()[x][y][z].c.g,_func.vertex3D()[x][y][z].c.b, 0.9f);
            glVertex3f(_func.vertex3D()[x][y][z].d.x, _func.vertex3D()[x][y][z].d.y, _func.vertex3D()[x][y][z].d.z);
        }
    }
    // xz
    for(int z = 0; z < _zsize; z++){
        for(int x = 0; x < _xsize; x++){
            int y = _yslice;
            glColor4f(_func.vertex3D()[x][y][z].c.r,_func.vertex3D()[x][y][z].c.g,_func.vertex3D()[x][y][z].c.b, 0.9f);
            glVertex3f(_func.vertex3D()[x][y][z].d.x, _func.vertex3D()[x][y][z].d.y, _func.vertex3D()[x][y][z].d.z);
        }
    }
    glEnd();
}
//===============================================
void GOpenGL::position(float _alpha, float _beta, float _zoom) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -_zoom);
    glRotatef(_beta, 1.0, 0.0, 0.0);
    glRotatef(_alpha, 0.0, 0.0, 1.0);
}
//===============================================
void GOpenGL::camera(float _fovY, float _front, float _back, int width, int height) {
    const double DEG2RAD = 3.14159265 / 180;
    m_ratio = 1.f; m_width = width; m_height = height;
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
glm::mat4 GOpenGL::camera(const sGCamera& _cam) {
    return glm::lookAt(_cam.eye, _cam.center, _cam.up);
}
//===============================================
void GOpenGL::origin(float _linesize, float _transparency) {
    glLineWidth(_linesize);
    glBegin(GL_LINES);
    // x-axis
    glColor4f(1.f, 0.f, 0.f, _transparency);
    glVertex3f(0.f, 0.f, 0.f);
    glColor4f(1.f, 0.f, 0.f, _transparency);
    glVertex3f(0.3f, 0.f, 0.f);
    // y-axis
    glColor4f(0.f, 1.f, 0.f, _transparency);
    glVertex3f(0.f, 0.f, 0.f);
    glColor4f(0.f, 1.f, 0.f, _transparency);
    glVertex3f(0.f, 0.f, 0.3f);
    // z-axis
    glColor4f(0.f, 0.f, 1.f, _transparency);
    glVertex3f(0.f, 0.f, 0.f);
    glColor4f(0.f, 0.f, 1.f, _transparency);
    glVertex3f(0.f, 0.3f, 0.f);
    glEnd();
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
void GOpenGL::uniform(const char* _name, GLfloat _v0) {
    GLint lLocation = glGetUniformLocation(m_program, _name);
    glUniform1f(lLocation, _v0);
}
//===============================================
void GOpenGL::uniform(const char* _name, GLfloat _v0, GLfloat _v1, GLfloat _v2) {
    GLint lLocation = glGetUniformLocation(m_program, _name);
    glUniform3f(lLocation, _v0, _v1, _v2);
}
//===============================================
void GOpenGL::uniform(const char* _name, GLfloat _v0, GLfloat _v1, GLfloat _v2, GLfloat _v3) {
    GLint lLocation = glGetUniformLocation(m_program, _name);
    glUniform4f(lLocation, _v0, _v1, _v2, _v3);
}
//===============================================
void GOpenGL::uniform(const char* _name, const GLfloat* _v0) {
    GLint lLocation = glGetUniformLocation(m_program, _name);
    glUniformMatrix4fv(lLocation, 1, GL_FALSE, _v0);
}
//===============================================
void GOpenGL::uniform(const char* _name, const glm::vec3 &_vec) {
    uniform(_name, _vec.x, _vec.y, _vec.z);
}
//===============================================
void GOpenGL::uniform(const char* _name, const glm::vec4 &_vec) {
    uniform(_name, _vec.x, _vec.y, _vec.z, _vec.w);
}
//===============================================
void GOpenGL::uniform(const char* _name, const glm::mat4 &_mat) {
    GLint lLocation = glGetUniformLocation(m_program, _name);
    glUniformMatrix4fv(lLocation, 1, GL_FALSE, &_mat[0][0]);
}
//===============================================
void GOpenGL::uniform2(const char* _name, GLuint _v0) {
    GLint lLocation = glGetUniformLocation(m_program, _name);
    glUniform1i(lLocation, _v0);
}
//===============================================
