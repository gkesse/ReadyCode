//===============================================
#include "GImagePyramid.h"
#include "GManager.h"
//===============================================
GImagePyramid::GImagePyramid(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GImagePyramid::~GImagePyramid() {

}
//===============================================
void GImagePyramid::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    cv::Mat img1, img2;

    cv::namedWindow( "ReadyApp-1", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "ReadyApp-2", cv::WINDOW_AUTOSIZE );

    img1 = cv::imread( lApp->opencv_image_file );
    cv::imshow( "ReadyApp-1", img1 );
    cv::pyrDown( img1, img2);
    cv::imshow( "ReadyApp-2", img2 );
    cv::waitKey(0);
}
//===============================================
