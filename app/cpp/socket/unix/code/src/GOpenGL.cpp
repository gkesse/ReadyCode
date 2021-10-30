//===============================================
#define STB_IMAGE_IMPLEMENTATION
//===============================================
#include "GOpenGL.h"
#include "GFunction.h"
#include "GFile.h"
//===============================================
#include <stb_image.h>
//===============================================
GOpenGL::GOpenGL() {
    m_window = 0;
    m_width = 400;
    m_height = 400;
    m_title = "ReadyApp";
    m_ratio = 0.f;
    m_programID = 0;
    m_textureID = 0;
    m_pipelineID = 0;
    m_blockBuffer = 0;
    m_blockSize = 0;
    m_indices = 0;
    m_offset = 0;
}
//===============================================
GOpenGL::~GOpenGL() {
    if(m_programID != -1) {deleteProgram();}
    if(m_textureID != -1) {deleteTexture();}
}
//===============================================
void GOpenGL::width(int _width) {
    m_width = _width;
}
//===============================================
int GOpenGL::width() {
    return m_width;
}
//===============================================
void GOpenGL::height(int _height) {
    m_height = _height;
}
//===============================================
int GOpenGL::height() {
    return m_height;
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
    glEnable(GL_ALPHA_TEST);
}
//===============================================
void GOpenGL::init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(m_width, m_height);
    glutCreateWindow(m_title.c_str());
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
void GOpenGL::init2() {
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
    glewExperimental = true;
    glewInit();
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

    printf("GL Vendor.......: %s\n", vendor);
    printf("GL Renderer.....: %s\n", renderer);
    printf("GL Version......: %s\n", version);
    printf("GL Version......: %d.%d\n", major, minor);
    printf("GLSL Version....: %s\n", glslVersion);
    printf("MSAA samples....: %d\n", samples);
    printf("MSAA buffers....: %d\n", sampleBuffers);

    GLint nExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
    for( int i = 0; i < nExtensions; i++ ) {
        printf("Ext[%3d]........: %s\n", i, glGetStringi(GL_EXTENSIONS, i));
    }
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
void GOpenGL::pipeline(const GOpenGL& _vertex, const GOpenGL& _fragment) {
    glCreateProgramPipelines(1, &m_pipelineID);
    glUseProgramStages(m_pipelineID, GL_VERTEX_SHADER_BIT, _vertex.m_programID);
    glUseProgramStages(m_pipelineID, GL_FRAGMENT_SHADER_BIT, _fragment.m_programID);
}
//===============================================
void GOpenGL::pipeline() {
    glBindProgramPipeline(m_pipelineID);
}
//===============================================
void GOpenGL::attributs() {
    GLint lCount;
    glGetProgramInterfaceiv(m_programID, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &lCount);
    GLenum lProperties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION};

    printf("Active attributes.....:\n");
    for(int i = 0; i < lCount; i++) {
        GLint lResults[3];
        glGetProgramResourceiv(m_programID, GL_PROGRAM_INPUT, i, 3, lProperties, 3, NULL, lResults);
        GLint lSize = lResults[0] + 1;
        char* lName = new char[lSize];
        glGetProgramResourceName(m_programID, GL_PROGRAM_INPUT, i, lSize, NULL, lName);
        printf(".....[%-5d] : %s (%s)\n", lResults[2], lName, type(lResults[1]));
        delete[] lName;
    }
}
//===============================================
void GOpenGL::attribut(GLuint _location, GLint _size, GLuint _offset) {
    glVertexAttribFormat(_location, _size, GL_FLOAT, GL_FALSE, _offset);
    glVertexAttribBinding(_location, _location);
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
void GOpenGL::use() {
    glUseProgram(m_programID);
}
//===============================================
void GOpenGL::use(GLuint _programID) {
    glUseProgram(_programID);
}
//===============================================
void GOpenGL::fragment(GLuint _location, const char* _name) {
    glBindFragDataLocation(m_programID, _location, _name);
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
    glDeleteProgram(m_programID);
    m_programID = -1;
}
//===============================================
void GOpenGL::deleteTexture() {
    glDeleteTextures(1, &m_textureID);
    m_textureID = -1;
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
void GOpenGL::onDisplay(void (*_func)(void)) {
    glutDisplayFunc(_func);
}
//===============================================
void GOpenGL::onDisplay(sGParams4& _params) {
    glClearColor(0.1f, 0.1f, 0.4f, 0.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glPushMatrix();
    coordinate(_params.cam, _params.rho, _params.theta, _params.phi);
    gluLookAt(
            _params.cam.eye[0], _params.cam.eye[1], _params.cam.eye[2],
            _params.cam.center[0], _params.cam.center[1], _params.cam.center[2],
            _params.cam.up[0], _params.cam.up[1], _params.cam.up[2]
    );
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 5.0f, 0.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f );
    if(_params.solid > 0) {glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);}
    else {glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);}
    glDrawElements(GL_QUADS, _params.indice, GL_UNSIGNED_INT, _params.indices);
    if(_params.normal > 0) {normal(_params.vertex, _params.normals, _params.ncircle, _params.nvertex, _params.pointsize);}
    glPopMatrix();
    glutSwapBuffers();
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
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(_vertex[0], _vertex[1], _vertex[2]);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(_vertex[0] + _normal[0], _vertex[1] + _normal[1], _vertex[2] + _normal[2]);
    glEnd();
}
//===============================================
void GOpenGL::indices(sGParams4& _params) {
    for(int j = 0, k = 0; j < _params.ncircle - 1; j++) {
        int offset = j*_params.nvertex;

        for(int i = 0; i < _params.nvertex - 1; i++) {
            _params.indices[k++] = i + offset;
            _params.indices[k++] = i + 1 + offset;
            _params.indices[k++] = i + _params.nvertex + 1 + offset;
            _params.indices[k++] = i + _params.nvertex + offset;
        }

        _params.indices[k++] = _params.nvertex - 1 + offset;
        _params.indices[k++] = offset;
        _params.indices[k++] = _params.nvertex + offset;
        _params.indices[k++] = _params.nvertex*2 - 1 + offset;
    }
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
void GOpenGL::triangle(GLint _index, GLsizei _count) {
    glDrawArrays(GL_TRIANGLES, _index, _count);
}
//===============================================
void GOpenGL::triangle2(const void* _indices, GLsizei _count) {
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, _indices);
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
glm::mat4 GOpenGL::camera(const sGCamera& _cam) {
    return glm::lookAt(_cam.eye, _cam.center, _cam.up);
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
void GOpenGL::depthOn() {
    glEnable(GL_DEPTH_TEST);
}
//===============================================
void GOpenGL::depthOff() {
    glDisable(GL_DEPTH_TEST);
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
void GOpenGL::uniform(const char* _name, const GGml& _mat) {
    GLint lLocation = glGetUniformLocation(m_programID, _name);
    glUniformMatrix4fv(lLocation, 1, GL_FALSE, &_mat.mat4()[0][0]);
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
void GOpenGL::angle(bool _animate, float& _angle) {
    if(_animate) {
        _angle += 0.1f;
        if(_angle >= 360.0f) _angle -= 360.0f;
    }
}
//===============================================
void GOpenGL::rotation(glm::mat4& _rotation, float _angle) {
    _rotation = glm::rotate(glm::mat4(1.0f), _angle, glm::vec3(0.0f, 0.0f, 1.0f));
}
//===============================================
