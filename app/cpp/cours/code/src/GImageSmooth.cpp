//===============================================
#include "GImageSmooth.h"
#include "GManager.h"
//===============================================
GImageSmooth::GImageSmooth(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GImageSmooth::~GImageSmooth() {

}
//===============================================
void GImageSmooth::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    cv::namedWindow( "ReadyApp-in", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "ReadyApp-out", cv::WINDOW_AUTOSIZE );

    cv::Mat image = cv::imread(lApp->opencv_image_file, -1);
    if( image.empty() ) {return;}

    cv::imshow( "ReadyApp-in", image );
    cv::Mat out;
    cv::GaussianBlur( image, out, cv::Size(5,5), 3, 3);
    cv::GaussianBlur( out, out, cv::Size(5,5), 3, 3);

    cv::imshow( "ReadyApp-out", out );
    cv::waitKey( 0 );
}
//===============================================
