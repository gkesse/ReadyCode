//===============================================
#include "GOpenCV.h"
//===============================================
GOpenCV::GOpenCV() {
	m_title = "ReadyApp";
}
//===============================================
GOpenCV::~GOpenCV() {

}
//===============================================
void GOpenCV::filename(const std::string _filename) {
	m_filename = _filename;
}
//===============================================
void GOpenCV::title(const std::string _title) {
	m_title = _title;
}
//===============================================
void GOpenCV::showImage() {
	cv::Mat lImg = cv::imread(m_filename, cv::IMREAD_UNCHANGED);
	cv::namedWindow(m_title, cv::WINDOW_AUTOSIZE);
	cv::imshow(m_title, lImg);
	cv::waitKey(0);
	cv::destroyWindow(m_title);
}
//===============================================
