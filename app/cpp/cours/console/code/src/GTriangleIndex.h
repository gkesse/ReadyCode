//===============================================
#ifndef _GTriangleIndex_
#define _GTriangleIndex_
//===============================================
#include "GOpenGLUi.h"
//===============================================
class GTriangleIndex : public GOpenGLUi {
public:
    GTriangleIndex();
    virtual ~GTriangleIndex();
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
