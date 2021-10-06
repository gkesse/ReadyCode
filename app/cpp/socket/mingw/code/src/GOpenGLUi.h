//===============================================
#ifndef _GOpenGLUi_
#define _GOpenGLUi_
//===============================================
#include "GInclude.h"
#include "GOpenGL.h"
//===============================================
class GOpenGLUi {
public:
    GOpenGLUi();
    virtual ~GOpenGLUi();
    static GOpenGLUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
    static void onResize(GLFWwindow* _window, int _width, int _height);
    static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	static GOpenGL lOpenGL;
	static sGParams lParams;
};
//==============================================
#endif
//==============================================
