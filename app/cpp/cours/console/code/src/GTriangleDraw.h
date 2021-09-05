//===============================================
#ifndef _GTriangleDraw_
#define _GTriangleDraw_
//===============================================
#include "GOpenGLUi.h"
//===============================================
class GTriangleDraw : public GOpenGLUi {
public:
    GTriangleDraw();
    virtual ~GTriangleDraw();
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
