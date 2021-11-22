//===============================================
#include "GOpenCVUi.h"
#include "GOpenCV.h"
#include "GManager.h"
//===============================================
GOpenCV GOpenCVUi::lOpenCV;
sGParams GOpenCVUi::lParams;
//===============================================
GOpenCVUi::GOpenCVUi() {

}
//===============================================
GOpenCVUi::~GOpenCVUi() {

}
//===============================================
GOpenCVUi* GOpenCVUi::Create(const std::string& key) {
    if(key == "default") {return new GOpenCVUi;}
    return new GOpenCVUi;
}
//===============================================
void GOpenCVUi::run(int argc, char** argv) {
    sGApp* lApp = GResource::Instance()->getData()->app;

    lOpenCV.filename(lApp->video_file);
    lOpenCV.open();
    lOpenCV.read();
    lOpenCV.window();

    GOpenCV lWriter;
    lWriter.filename(lApp->video_file2);
    lWriter.fps(lOpenCV);
    lWriter.size2(lOpenCV);
    lWriter.open2();

    while(1) {
        lOpenCV.read();
        if(lOpenCV.empty()) break;
        lOpenCV.gray(lOpenCV);
        lOpenCV.bgr(lOpenCV);
        lWriter.write(lOpenCV);
        lOpenCV.show();
        if(!lOpenCV.wait(33)) break;
    }
}
//===============================================
void GOpenCVUi::onTrackbar(int _pos, void* _params) {
    lOpenCV.onTrackbar(_pos, lParams.run, lParams.dontset);
}
//===============================================
