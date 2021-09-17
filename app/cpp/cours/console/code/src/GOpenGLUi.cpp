//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
//===============================================
typedef struct _sGParams sGParams;
//===============================================
struct _sGParams {
    float deltaTime;
    float lastFrame;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
};
//===============================================
void* GOpenGLUi::m_params = 0;
//===============================================
GOpenGLUi::GOpenGLUi() {

}
//===============================================
GOpenGLUi::~GOpenGLUi() {

}
//===============================================
GOpenGLUi* GOpenGLUi::Create(const std::string& key) {
    if(key == "default") {return new GOpenGLUi;}
    return new GOpenGLUi;
}
//===============================================
void GOpenGLUi::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    glfwSetErrorCallback(onError);

    if (!glfwInit()) {
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ReadyApp", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwSetKeyCallback(window, onKey);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, onResize);

    glEnable(GL_DEPTH_TEST);

    unsigned int shaderProgram = GManager::Instance()->loadShaders(
            lApp->shader_vertex_file, lApp->shader_fragment_file);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1 = GManager::Instance()->loadTexture2(lApp->texture_file);
    unsigned int texture2 = GManager::Instance()->loadTexture(lApp->texture_file_02);

    GManager::Instance()->useProgram(shaderProgram);
    GManager::Instance()->setUniform(shaderProgram, "texture1", 0);
    GManager::Instance()->setUniform(shaderProgram, "texture2", 1);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    GManager::Instance()->setUniform(shaderProgram, "projection", projection);

    sGParams* lParams = new sGParams;
    m_params = lParams;

    lParams->deltaTime = 0.0f;
    lParams->lastFrame = 0.0f;

    lParams->cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    lParams->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    lParams->cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        lParams->deltaTime = currentFrame - lParams->lastFrame;
        lParams->lastFrame = currentFrame;
        //===============================================
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //===============================================
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        //===============================================
        GManager::Instance()->useProgram(shaderProgram);
        //===============================================
        glm::mat4 view = glm::lookAt(lParams->cameraPos, lParams->cameraPos + lParams->cameraFront, lParams->cameraUp);
        GManager::Instance()->setUniform(shaderProgram, "view", view);
        glBindVertexArray(VAO);
        //===============================================
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (i + 1);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            GManager::Instance()->setUniform(shaderProgram, "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //===============================================
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();
}
//===============================================
void GOpenGLUi::onResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
//===============================================
void GOpenGLUi::onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    sGParams* lParams = (sGParams*)m_params;

    float cameraSpeed = 2.5 * lParams->deltaTime;

    if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
    	lParams->cameraPos += cameraSpeed * lParams->cameraFront;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {
    	lParams->cameraPos -= cameraSpeed * lParams->cameraFront;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT) {
    	lParams->cameraPos -= glm::normalize(glm::cross(lParams->cameraFront, lParams->cameraUp)) * cameraSpeed;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT) {
    	lParams->cameraPos += glm::normalize(glm::cross(lParams->cameraFront, lParams->cameraUp)) * cameraSpeed;
    }
}
//===============================================
void GOpenGLUi::onError(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
//===============================================
