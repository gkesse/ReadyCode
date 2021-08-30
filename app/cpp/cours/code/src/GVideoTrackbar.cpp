//===============================================
#include "GVideoTrackbar.h"
#include "GManager.h"
//===============================================
typedef struct _sGParams sGParams;
//===============================================
struct _sGParams {
    cv::VideoCapture g_cap;
    int g_slider_position;
    int g_run;
    int g_dontset;
};
//===============================================
GVideoTrackbar::GVideoTrackbar(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GVideoTrackbar::~GVideoTrackbar() {

}
//===============================================
void GVideoTrackbar::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    sGParams* lParams = new sGParams;
    lParams->g_slider_position = 0;
    lParams->g_run = 1;
    lParams->g_dontset = 0;

    cv::namedWindow( "ReadyApp", cv::WINDOW_AUTOSIZE );
    lParams->g_cap.open( lApp->opencv_video_file );
    int frames = (int) lParams->g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw = (int) lParams->g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph = (int) lParams->g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "Video has " << frames << " frames of dimensions("
            << tmpw << ", " << tmph << ")." << "\n";

    cv::createTrackbar("Position", "ReadyApp", &lParams->g_slider_position, frames, onTrackbarSlide, lParams);
    cv::Mat frame;

    while(1) {
        if( lParams->g_run != 0 ) {
            lParams->g_cap >> frame; if(frame.empty()) {break;}
            int current_pos = (int)lParams->g_cap.get(cv::CAP_PROP_POS_FRAMES);
            lParams->g_dontset = 1;
            cv::setTrackbarPos("Position", "ReadyApp", current_pos);
            cv::imshow( "ReadyApp", frame );
            lParams->g_run -= 1;
        }

        char c = (char) cv::waitKey(10);
        // single step
        if( c == 's' ) {
            lParams->g_run = 1; std::cout << "Single step, run = " << lParams->g_run << "\n";
        }
        // run mode
        if( c == 'r' ) {
            lParams->g_run = -1; std::cout << "Run mode, run = " << lParams->g_run << "\n";
        }
        if( c == 27 ) {
            break;
        }
    }
}
//===============================================
void GVideoTrackbar::onTrackbarSlide( int pos, void* params ) {
    sGParams* lParams = (sGParams*)params;
    lParams->g_cap.set( cv::CAP_PROP_POS_FRAMES, pos );
    if( !lParams->g_dontset ) {
        lParams->g_run = 1;
    }
    lParams->g_dontset = 0;
}
//===============================================
