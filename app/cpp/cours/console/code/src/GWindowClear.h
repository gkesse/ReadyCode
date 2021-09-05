//===============================================
#ifndef _GWindowClear_
#define _GWindowClear_
//===============================================
#include "GOpenGLUi.h"
//===============================================
class GWindowClear : public GOpenGLUi {
public:
    GWindowClear();
    virtual ~GWindowClear();
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
