//===============================================
#include "GOpenCVUi.h"
#include "GImageLoad.h"
#include "GVideoLoad.h"
#include "GVideoTrackbar.h"
//===============================================
GOpenCVUi::GOpenCVUi(QObject* parent) :
QObject(parent) {

}
//===============================================
GOpenCVUi::~GOpenCVUi() {

}
//===============================================
GOpenCVUi* GOpenCVUi::Create(const QString& key) {
    if(key == "default") {return new GOpenCVUi;}
    if(key == "image/load") {return new GImageLoad;}
    if(key == "video/load") {return new GVideoLoad;}
    if(key == "video/trackbar") {return new GVideoTrackbar;}
    return new GOpenCVUi;
}
//===============================================
void GOpenCVUi::run(int argc, char** argv) {}
//===============================================
