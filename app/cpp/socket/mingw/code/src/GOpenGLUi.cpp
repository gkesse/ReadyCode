//===============================================
#include "GOpenGLUi.h"
#include "GOpenGL.h"
#include "data_ecg.h"
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
    GOpenGL lOpenGL;
    lOpenGL.init();

    int lCount = 0;

    while (!lOpenGL.isClose()) {
        lOpenGL.viewport();
        lOpenGL.grid(5.f, 1.f, 0.1f);
        lOpenGL.axis(5.f, 1.f , 5.f, {1.f, 1.f, 1.f, 0.5f});
        if(lCount > 5000) {lCount = 0;}
        lCount += 5;
        lOpenGL.ecg(data_ecg, lCount, 1024, 2.f);
        lOpenGL.pollEvents();
    }

    lOpenGL.close();
}
//===============================================
