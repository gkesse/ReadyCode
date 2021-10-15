//===============================================
#include "GOpenCVUi.h"
#include "GOpenCV.h"
#include "GManager.h"
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
	GOpenCV lOpenCV;
	lOpenCV.filename(lApp->image_file);
	lOpenCV.showImage();
}
//===============================================
