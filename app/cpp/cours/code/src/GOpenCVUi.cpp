//===============================================
#include "GOpenCVUi.h"
// image
#include "GImageLoad.h"
#include "GImageSmooth.h"
#include "GImagePyramid.h"
#include "GImageCanny.h"
#include "GImagePixel.h"
#include "GImageBlend.h"
// video
#include "GVideoLoad.h"
#include "GVideoTrackbar.h"
#include "GVideoCamera.h"
#include "GVideoWrite.h"
#include "GVideoCodec.h"
// file
#include "GFileWrite.h"
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
    if(key == "image/blend") {return new GImageBlend;}
    // video
    if(key == "video/load") {return new GVideoLoad;}
    if(key == "video/trackbar") {return new GVideoTrackbar;}
    if(key == "video/camera") {return new GVideoCamera;}
    if(key == "video/write") {return new GVideoWrite;}
    if(key == "video/codec") {return new GVideoCodec;}
    // file
    if(key == "file/write") {return new GFileWrite;}
    // default
    return new GOpenCVUi;
}
//===============================================
void GOpenCVUi::run(int argc, char** argv) {}
//===============================================
