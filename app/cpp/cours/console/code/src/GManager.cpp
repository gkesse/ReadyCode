//===============================================
#define STB_IMAGE_IMPLEMENTATION
//===============================================
#include "GManager.h"
//===============================================
#include <stb_image.h>
//===============================================
GManager* GManager::m_instance = 0;
//===============================================
GManager::GManager() {
    // manager
    mgr = new sGManager;
    // app
    mgr->app = new sGApp;
    mgr->app->app_name = "ReadyApp";
    mgr->app->shader_vertex_file = "data/shader/vertex_shader.vs";
    mgr->app->shader_fragment_file = "data/shader/fragment_shader.fs";
    mgr->app->texture_file = "data/texture/container.jpg";
    mgr->app->texture_file_flip = "data/texture/awesomeface.png";
}
//===============================================
GManager::~GManager() {

}
//===============================================
GManager* GManager::Instance() {
    if(m_instance == 0) {
        m_instance = new GManager;
    }
    return m_instance;
}
//===============================================
sGManager* GManager::getData() {
    return mgr;
}
//===============================================
unsigned int GManager::loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}
//===============================================
unsigned int GManager::loadShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) {
    unsigned int shaderProgram;
    std::string vertexSharderCode;
    std::string fragmentShaderCode;
    std::ifstream vertexShaderFileIn;
    std::ifstream fragmentShaderFileIn;

    vertexShaderFileIn.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFileIn.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexShaderFileIn.open(vertexShaderFile.c_str());
        fragmentShaderFileIn.open(fragmentShaderFile.c_str());
        std::stringstream vertexShaderStream, fragmentShaderStream;

        vertexShaderStream << vertexShaderFileIn.rdbuf();
        fragmentShaderStream << fragmentShaderFileIn.rdbuf();

        vertexShaderFileIn.close();
        fragmentShaderFileIn.close();

        vertexSharderCode   = vertexShaderStream.str();
        fragmentShaderCode = fragmentShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vertexShaderSource = vertexSharderCode.c_str();
    const char* fragmentShaderSource = fragmentShaderCode.c_str();
    return loadShaders(vertexShaderSource, fragmentShaderSource);
}
//===============================================
unsigned int GManager::loadTexture(const std::string& textureFile, bool flip) {
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    if(flip) {stbi_set_flip_vertically_on_load(true);}
    unsigned char *data = stbi_load(textureFile.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}
//===============================================
void GManager::setBool(unsigned int programId, const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}
//===============================================
void GManager::setInt(unsigned int programId, const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}
//===============================================
void GManager::setFloat(unsigned int programId, const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}
//===============================================
void GManager::useProgram(unsigned int programId) {
    glUseProgram(programId);
}
//===============================================
