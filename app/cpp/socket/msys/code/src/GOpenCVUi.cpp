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
    sGApp* lApp = GManager::Instance()->data()->app;

    float lPriors[] = {1.0, 10.0};

    lOpenCV.filename(lApp->train_file);
    lOpenCV.train();
    lOpenCV.split();
    lOpenCV.tree();
    lOpenCV.priors(1, 2, lPriors);
    lOpenCV.maxDepth(8);
    lOpenCV.minSample(10);
    lOpenCV.accuracy(0.01f);
    lOpenCV.surrogates(false);
    lOpenCV.surrogates(false);
    lOpenCV.surrogates(false);
    lOpenCV.print();
}
//===============================================
void GOpenCVUi::onTrackbar(int _pos, void* _params) {
    lOpenCV.onTrackbar(_pos, lParams.run, lParams.dontset);
}
//===============================================
