//===============================================
#include "GOpenGLUi.h"
#include "GManager.h"
#include "GOpenGL.h"
#include "GFunction.h"
#include "GThread.h"
#include "GSocket.h"
#include "data_ecg.h"
//===============================================
GOpenGL GOpenGLUi::lOpenGL;
sGOpenGL GOpenGLUi::lParams;
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
void GOpenGLUi::run(int _argc, char** _argv) {
    sGApp* lApp = GManager::Instance()->data()->app;

    lParams.win.width = 400;
    lParams.win.height = 400;
    lParams.win.title = "ReadyApp";
    lParams.win.bgcolor = {0.2f, 0.2f, 0.f, 1.f};

    lParams.grid.width = 5.f;
    lParams.grid.height = 1.f;
    lParams.grid.gridWidth = 1.f;
    lParams.grid.axisWidth = 10.f;
    lParams.grid.pointsize = 10.f;
    lParams.grid.gridDiv = {0.1f, 0.1f, 0.1f};
    lParams.grid.axisDiv = {1.f, 5/10.f, 1.f};
    lParams.grid.gridColor = {1.f, 1.f, 1.f, 1.f};
    lParams.grid.axisColor = {0.3f, 0.3f, 1.f, 0.5f};
    lParams.grid.pointColor = {1.f, 0.3f, 0.3f, 0.8f};
    lParams.grid.xrange = {0.f, 5.f};
    lParams.grid.yrange = {-5.f, 5.f};
    lParams.grid.zrange = {-1.f, 1.f};
    lParams.grid.origin = {0.f, -9.f, 0.f};

    lOpenGL.glfw();
    lOpenGL.window(lParams.win);
    lOpenGL.context();
    lOpenGL.pointOn();
    lOpenGL.lineOn();
    lOpenGL.blendOn();

    GThread lServer;
    lServer.create(onServer, 0);
    GThread lClient;
    lClient.create(onClient, 0);

    while (!lOpenGL.isClose()) {
        lOpenGL.bgcolor(lParams.win.bgcolor);
        lOpenGL.depthBuffer();
        lOpenGL.size(lParams.win);
        lOpenGL.ratio(lParams.win);
        lOpenGL.viewport(lParams.win);
        lOpenGL.projection();
        lOpenGL.ortho(lParams.win);
        lOpenGL.modelview();

        lOpenGL.origin(lParams.grid);
        lOpenGL.gridXY(lParams.grid);
        lOpenGL.axisXY(lParams.grid);
        lOpenGL.point(lParams.grid, {1.f, 2.f});

        lOpenGL.pollEvents();
    }

    lOpenGL.close();
}
//===============================================
void GOpenGLUi::onResize(GLFWwindow* _window, int _width, int _height) {

}
//===============================================
void GOpenGLUi::onKey(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {

}
//===============================================
void GOpenGLUi::onScroll(GLFWwindow* _window, double _x, double _y) {

}
//===============================================
void GOpenGLUi::onMouse(GLFWwindow* _window, int _button, int _action, int _mods) {

}
//===============================================
void GOpenGLUi::onCursor(GLFWwindow* _window, double _x, double _y) {

}
//===============================================
void GOpenGLUi::onDisplay() {

}
//===============================================
DWORD WINAPI GOpenGLUi::onServer(LPVOID _params) {
    GSocket lServer;
    sGSocket lParams;
    lParams.on_start = (void*)onStart;
    lServer.start(lParams);
    return 0;
}
//===============================================
DWORD WINAPI GOpenGLUi::onClient(LPVOID _params) {
    GSocket lServer;
    sGSocket lParams;
    lParams.address_ip = "127.0.0.1";
    std::string lData;
    lServer.call(lParams, "Bonjour tout le monde", lData);
    printf("Data.........: %s\n", lData.c_str());
    return 0;
}
//===============================================
DWORD WINAPI GOpenGLUi::onStart(LPVOID _params) {
    sGSocket* lSocket = (sGSocket*)_params;
    GSocket* lClient = lSocket->socket;
    std::string lData;
    lClient->reads(lData);
    lClient->writes("OK");
    printf("Client IP....: %s\n", lSocket->client_ip.c_str());
    printf("Data.........: %s\n", lData.c_str());
    lClient->close();
    delete lClient;
    return 0;
}
//===============================================
