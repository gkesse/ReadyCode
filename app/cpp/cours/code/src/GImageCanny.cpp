//===============================================
#include "GImageCanny.h"
#include "GManager.h"
//===============================================
GImageCanny::GImageCanny(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GImageCanny::~GImageCanny() {

}
//===============================================
void GImageCanny::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    cv::Mat img_rgb, img_gry, img_cny;
    cv::namedWindow( "ReadyApp Gray", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "ReadyApp Canny", cv::WINDOW_AUTOSIZE );

    img_rgb = cv::imread( lApp->opencv_image_file );

    cv::cvtColor( img_rgb, img_gry, cv::COLOR_BGR2GRAY);
    cv::imshow( "ReadyApp Gray", img_gry );
    cv::Canny( img_gry, img_cny, 10, 100, 3, true );
    cv::imshow( "ReadyApp Canny", img_cny );
    cv::waitKey(0);
}
//===============================================
