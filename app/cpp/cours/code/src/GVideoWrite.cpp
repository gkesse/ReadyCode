//===============================================
#include "GVideoWrite.h"
#include "GManager.h"
//===============================================
GVideoWrite::GVideoWrite(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GVideoWrite::~GVideoWrite() {

}
//===============================================
void GVideoWrite::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    cv::namedWindow( "ReadyApp", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "ReadyApp-2", cv::WINDOW_AUTOSIZE );

    cv::VideoCapture capture( lApp->opencv_video_file );

    double fps = capture.get( cv::CAP_PROP_FPS );
    cv::Size size(
            (int)capture.get( cv::CAP_PROP_FRAME_WIDTH ),
            (int)capture.get( cv::CAP_PROP_FRAME_HEIGHT )
    );
    cv::VideoWriter writer;
    writer.open( lApp->opencv_video_write, cv::VideoWriter::fourcc('M','J','P','G'), fps, size );
    cv::Mat bgr_frame, bgr_frame_2;

    while(1) {
        capture >> bgr_frame;
        if( bgr_frame.empty() ) {break;}
        cv::imshow( "ReadyApp", bgr_frame );
        cv::cvtColor( bgr_frame, bgr_frame_2, cv::COLOR_BGR2GRAY);
        cv::cvtColor( bgr_frame_2, bgr_frame_2, cv::COLOR_GRAY2BGR);
        cv::imshow( "ReadyApp-2", bgr_frame_2 );
        writer << bgr_frame_2;
        char c = cv::waitKey(10);
        if( c == 27 ) {break;}
    }
    capture.release();
}
//===============================================
