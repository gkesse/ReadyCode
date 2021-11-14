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
    virtual void run(int _argc, char** _argv);
    static void onResize(GLFWwindow* _window, int _width, int _height);
    static void onKey(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
    static void onScroll(GLFWwindow* _window, double _x, double _y);
    static void onMouse(GLFWwindow* _window, int _button, int _action, int _mods);
    static void onCursor(GLFWwindow* _window, double _x, double _y);
    static void onDisplay();
    static DWORD WINAPI onServer(LPVOID _params);
    static DWORD WINAPI onClient(LPVOID _params);
    static DWORD WINAPI onStart(LPVOID _params);

private:
    static GOpenGL lOpenGL;
    static sGOpenGL lParams;
};
//==============================================
#endif
//==============================================