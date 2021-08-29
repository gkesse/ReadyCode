//===============================================
#include "GVideoLoad.h"
#include "GManager.h"
//===============================================
GVideoLoad::GVideoLoad(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GVideoLoad::~GVideoLoad() {

}
//===============================================
void GVideoLoad::run(int argc, char** argv) {
	sGApp* lApp = GManager::Instance()->getData()->app;
	cv::namedWindow( "ReadyApp", cv::WINDOW_AUTOSIZE );
	cv::VideoCapture cap;
	cap.open( lApp->opencv_video_file );
	cv::Mat frame;
	while(1) {
		cap >> frame;
		if( frame.empty() ) {break;}
		cv::imshow( "ReadyApp", frame );
		if( cv::waitKey(33) >= 0 ) break;
	}
}
//===============================================
