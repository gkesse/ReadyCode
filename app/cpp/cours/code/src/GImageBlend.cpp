//===============================================
#include "GImageBlend.h"
#include "GManager.h"
//===============================================
GImageBlend::GImageBlend(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GImageBlend::~GImageBlend() {

}
//===============================================
void GImageBlend::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    cv::Mat src1 = cv::imread(lApp->opencv_image_file, 1);
    cv::Mat src2 = cv::imread(lApp->opencv_image_blend, 1);

    int w1 = src1.cols;
    int h1 = src1.rows;
    int w2 = src2.cols;
    int h2 = src2.rows;
    int x1 = w1 - w2 -10;
    int y1 = h1 - h2 - 10;

    double alpha = 1.0;
    double beta = 1.0;
    cv::Mat roi1( src1, cv::Rect(x1, y1, w2, h2) );
    cv::Mat roi2( src2, cv::Rect(0, 0, w2, h2) );
    cv::addWeighted( roi1, alpha, roi2, beta, 0.0, roi1 );
    cv::namedWindow( "ReadyApp", 1 );
    cv::imshow( "ReadyApp", src1 );
    cv::waitKey( 0 );
}
//===============================================
