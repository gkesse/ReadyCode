//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
// window
#include "GWindowCreate.h"
#include "GWindowClear.h"
// triangle
#include "GTriangleDraw.h"
#include "GTriangleIndex.h"
#include "GTriangleDouble.h"
//===============================================
GOpenGLUi::GOpenGLUi() {

}
//===============================================
GOpenGLUi::~GOpenGLUi() {

}
//===============================================
GOpenGLUi* GOpenGLUi::Create(const std::string& key) {
    if(key == "default") {return new GOpenGLUi;}
    // window
    if(key == "window/create") {return new GWindowCreate;}
    if(key == "window/clear") {return new GWindowClear;}
    // triangle
    if(key == "triangle/draw") {return new GTriangleDraw;}
    if(key == "triangle/index") {return new GTriangleIndex;}
    if(key == "triangle/double") {return new GTriangleDouble;}
    // default
    return new GOpenGLUi;
}
//===============================================
void GOpenGLUi::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ReadyApp", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    unsigned int shaderProgram = GManager::Instance()->loadShaders(
            lApp->shader_vertex_file, lApp->shader_fragment_file);

    float vertices[] = {
            // positions        // colors
            0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        //===============================================
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //===============================================
        float timeValue = glfwGetTime();
        float xOffset = sin(timeValue) / 2.0f;
        GManager::Instance()->setFloat(shaderProgram, "xOffset", xOffset);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //===============================================
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}
//===============================================
void GOpenGLUi::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
//===============================================
void GOpenGLUi::processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
//===============================================
