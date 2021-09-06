//===============================================
#include "GManager.h"
//===============================================
GManager* GManager::m_instance = 0;
//===============================================
GManager::GManager() {
	// manager
	mgr = new sGManager;
	// app
	mgr->app = new sGApp;
	mgr->app->app_name = "ReadyApp";
	mgr->app->shader_vertex_file = "C:\Users\Admin\Downloads\Programs\ReadyData\shader\vertex_shader.vs";
	mgr->app->shader_fragment_file = "C:\Users\Admin\Downloads\Programs\ReadyData\shader\fragment_shader.fs";
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
