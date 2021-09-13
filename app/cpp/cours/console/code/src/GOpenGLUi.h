//===============================================
#ifndef _GOpenGLUi_
#define _GOpenGLUi_
//===============================================
#include "GInclude.h"
//===============================================
class GOpenGLUi {
public:
    GOpenGLUi();
    virtual ~GOpenGLUi();
    static GOpenGLUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow *window);

private:
    const unsigned int SCR_WIDTH = 400;
    const unsigned int SCR_HEIGHT = 400;
};
//==============================================
#endif
//==============================================
