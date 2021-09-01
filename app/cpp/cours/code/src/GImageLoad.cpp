//===============================================
#include "GImageLoad.h"
#include "GManager.h"
//===============================================
GImageLoad::GImageLoad(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GImageLoad::~GImageLoad() {

}
//===============================================
void GImageLoad::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;
    cv::Mat img = cv::imread(lApp->opencv_image_file, -1);
    if( img.empty() ) {return;}
    cv::namedWindow( "ReadyApp", cv::WINDOW_AUTOSIZE );
    cv::imshow( "ReadyApp", img );
    cv::waitKey( 0 );
    cv::destroyWindow( "ReadyApp" );
}
//===============================================
