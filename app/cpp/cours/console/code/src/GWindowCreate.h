//===============================================
#ifndef _GWindowCreate_
#define _GWindowCreate_
//===============================================
#include "GOpenGLUi.h"
//===============================================
class GWindowCreate : public GOpenGLUi {
public:
    GWindowCreate();
    virtual ~GWindowCreate();
    void run(int argc, char** argv);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow *window);

private:
    const unsigned int SCR_WIDTH = 400;
    const unsigned int SCR_HEIGHT = 400;
};
//==============================================
#endif
//==============================================
