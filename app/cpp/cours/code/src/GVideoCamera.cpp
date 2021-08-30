//===============================================
#include "GVideoCamera.h"
#include "GManager.h"
//===============================================
GVideoCamera::GVideoCamera(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GVideoCamera::~GVideoCamera() {

}
//===============================================
void GVideoCamera::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;
    cv::namedWindow( "ReadyApp", cv::WINDOW_AUTOSIZE );
    cv::VideoCapture cap;
    cap.open( lApp->opencv_camera_index );
    cv::Mat frame;
    while(1) {
        cap >> frame;
        if( frame.empty() ) {break;}
        cv::imshow( "ReadyApp", frame );
        if( cv::waitKey(33) >= 0 ) break;
    }
}
//===============================================
