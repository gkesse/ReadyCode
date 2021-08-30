//===============================================
#include "GOpenCVUi.h"
// image
#include "GImageLoad.h"
#include "GImageSmooth.h"
#include "GImagePyramid.h"
#include "GImageCanny.h"
#include "GImagePixel.h"
// video
#include "GVideoLoad.h"
#include "GVideoTrackbar.h"
#include "GVideoCamera.h"
#include "GVideoWrite.h"
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
    // image
    if(key == "image/load") {return new GImageLoad;}
    if(key == "image/smooth") {return new GImageSmooth;}
    if(key == "image/pyramid") {return new GImagePyramid;}
    if(key == "image/canny") {return new GImageCanny;}
    if(key == "image/pixel") {return new GImagePixel;}
    // video
    if(key == "video/load") {return new GVideoLoad;}
    if(key == "video/trackbar") {return new GVideoTrackbar;}
    if(key == "video/camera") {return new GVideoCamera;}
    if(key == "video/write") {return new GVideoWrite;}
    // default
    return new GOpenCVUi;
}
//===============================================
void GOpenCVUi::run(int argc, char** argv) {}
//===============================================
