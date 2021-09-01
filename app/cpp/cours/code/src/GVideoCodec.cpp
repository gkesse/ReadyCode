//===============================================
#include "GVideoCodec.h"
#include "GManager.h"
//===============================================
GVideoCodec::GVideoCodec(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GVideoCodec::~GVideoCodec() {

}
//===============================================
void GVideoCodec::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    cv::VideoCapture cap;
    cap.open( lApp->opencv_video_file );

    unsigned f = (unsigned)cap.get( cv::CAP_PROP_FOURCC );

    char fourcc[] = {
            (char) f,
            (char)(f >> 8),
            (char)(f >> 16),
            (char)(f >> 24),
            '\0'
    };

    std::cout <<"FourCC for this video was: " << fourcc << std::endl;
}
//===============================================
