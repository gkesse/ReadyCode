//===============================================
#include "GOpenCV.h"
//===============================================
int GOpenCV::m_count = 0;
//===============================================
GOpenCV::GOpenCV() {
	m_count++;
	m_title = "ReadyApp";
	m_onTrackbar = 0;
	m_scaleFactor = 1.1;
	m_minNeighbors = 3;
	m_minSize = cv::Size(30, 30);
	m_maxSize = cv::Size();
	m_headerLine = 0;
	m_startIndex = 0;
	m_endIndex = 1;
	m_specType = "cat[0-22]";
	m_delimiter = ',';
	m_missch = '?';
	m_ratio = 0.9;
	m_performance = 0.f;
	m_good = 0;
	m_bad = 0;
	m_total = 0;
	if(m_count != 1) {m_title += "-" + std::to_string(m_count);}
}
//===============================================
GOpenCV::~GOpenCV() {

}
//===============================================
void GOpenCV::filename(const std::string& _filename) {
	m_filename = _filename;
}
//===============================================
void GOpenCV::title(const std::string& _title) {
	m_title = _title;
}
//===============================================
std::string GOpenCV::title() const {
	return m_title;
}
//===============================================
cv::Mat& GOpenCV::img() {
	return m_img;
}
//===============================================
void GOpenCV::window() {
	cv::namedWindow(m_title, cv::WINDOW_AUTOSIZE);
}
//===============================================
void GOpenCV::open() {
	m_cap.open(m_filename);
}
//===============================================
void GOpenCV::load() {
	m_img = cv::imread(m_filename);
}
//===============================================
int GOpenCV::width() const {
	return (int)m_cap.get(cv::CAP_PROP_FRAME_WIDTH);
}
//===============================================
int GOpenCV::width2() const {
	return m_img.cols;
}
//===============================================
int GOpenCV::height() const {
	return (int)m_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
}
//===============================================
int GOpenCV::height2() const {
	return m_img.rows;
}
//===============================================
void GOpenCV::scaleFactor(double _scaleFactor) {
	m_scaleFactor = _scaleFactor;
}
//===============================================
void GOpenCV::minNeighbors(int _minNeighbors) {
	m_minNeighbors = _minNeighbors;
}
//===============================================
void GOpenCV::minSize(int _width, int _height) {
	m_minSize= cv::Size(_width, _height);
}
//===============================================
void GOpenCV::maxSize(int _width, int _height) {
	m_maxSize= cv::Size(_width, _height);
}
//===============================================
int GOpenCV::frame() const {
	return (int)m_cap.get(cv::CAP_PROP_POS_FRAMES);
}
//===============================================
int GOpenCV::frames() const {
	return (int)m_cap.get(cv::CAP_PROP_FRAME_COUNT);
}
//===============================================
void GOpenCV::trackbar(const std::string& _name, int* _pos, int _count, void* _params) {
	cv::createTrackbar(_name, m_title, _pos, _count, m_onTrackbar, _params);
}
//===============================================
void GOpenCV::trackbar(const std::string& _name, int _pos) {
	cv::setTrackbarPos(_name, m_title, _pos);
}
//===============================================
void GOpenCV::onTrackbar(cv::TrackbarCallback _onTrackbar) {
	m_onTrackbar = _onTrackbar;
}
//===============================================
void GOpenCV::onTrackbar(int _pos, int& _run, int& _dontset) {
	m_cap.set(cv::CAP_PROP_POS_FRAMES, _pos);
	if(!_dontset) _run = 1;
	_dontset = 0;
}
//===============================================
bool GOpenCV::empty() const {
	return m_img.empty();
}
//===============================================
void GOpenCV::read() {
	m_cap >> m_img;
}
//===============================================
void GOpenCV::show() {
	cv::imshow(m_title, m_img);
}
//===============================================
void GOpenCV::show(GOpenCV& _out) {
	cv::imshow(m_title, _out.img());
}
//===============================================
void GOpenCV::show(const std::string& _title) {
	cv::imshow(_title, m_img);
}
//===============================================
void GOpenCV::wait() {
	cv::waitKey(0);
}
//===============================================
bool GOpenCV::wait(int _ms) {
	bool lContinue = true;
	char lChar = (char)cv::waitKey(_ms);
	if(lChar != -1) {lContinue = false;}
	return lContinue;
}
//===============================================
bool GOpenCV::wait(int _ms, int& _run) {
	bool lContinue = true;
	char lChar = (char)cv::waitKey(_ms);
	if(lChar == 's') {_run = 1;}
	if(lChar == 'r') {_run = -1;}
	if(lChar == 27) {lContinue = false;}
	return lContinue;
}
//===============================================
void GOpenCV::gaussian(GOpenCV& _out) {
	cv::GaussianBlur(m_img, _out.img(), cv::Size(5, 5), 3, 3);
}
//===============================================
void GOpenCV::pyramid(GOpenCV& _out) {
	cv::pyrDown(m_img, _out.img());
}
//===============================================
void GOpenCV::cascade() {
	m_cascade.reset(new cv::CascadeClassifier(m_filename));
}
//===============================================
void GOpenCV::gray(GOpenCV& _out) {
	cv::cvtColor(m_img, _out.img(), cv::COLOR_BGR2GRAY);
}
//===============================================
void GOpenCV::bgr(GOpenCV& _out) {
	cv::cvtColor(m_img, _out.img(), cv::COLOR_GRAY2BGR);
}
//===============================================
void GOpenCV::resize(GOpenCV& _out, int _width, int _height) {
	cv::resize(m_img, _out.img(), cv::Size(_width, _height), 0.0, 0.0, cv::INTER_LINEAR);
}
//===============================================
void GOpenCV::resize(GOpenCV& _out, double _factor) {
	cv::Size lSize(width2()*_factor, height2()*_factor);
	cv::resize(m_img, _out.img(), lSize, 0.0, 0.0, cv::INTER_LINEAR);
}
//===============================================
void GOpenCV::resize(double _factor) {
	resize(*this, _factor);
}
//===============================================
void GOpenCV::equalize(GOpenCV& _out) {
	cv::equalizeHist(m_img, _out.img());
}
//===============================================
void GOpenCV::objects() {
	m_cascade->detectMultiScale(
			m_img,
			m_objects,
			m_scaleFactor,
			m_minNeighbors,
			cv::CASCADE_DO_CANNY_PRUNING,
			m_minSize,
			m_maxSize
	);
}
//===============================================
void GOpenCV::objects(cv::Scalar* _colors, int _n, double _scale) {
	std::vector<cv::Rect>::iterator it = m_objects.begin();
	for(int i = 0; it != m_objects.end(); it++, i++) {
		cv::Rect lRect = (*it);
		lRect.x *= _scale;
		lRect.y *= _scale;
		lRect.width *= _scale;
		lRect.height *= _scale;
		cv::rectangle(m_img, lRect, _colors[i % _n]);
	}
}
//===============================================
void GOpenCV::objects(GOpenCV& _out, cv::Scalar* _colors, int _n, double _scale) {
	m_objects = _out.m_objects;
	objects(_colors, _n, _scale);
}
//===============================================
int GOpenCV::count() const {
	return m_objects.size();
}
//===============================================
void GOpenCV::train() {
	m_trainData = cv::ml::TrainData::loadFromCSV(
			m_filename,
			m_headerLine,
			m_startIndex,
			m_endIndex,
			m_specType,
			m_delimiter,
			m_missch
	);
}
//===============================================
void GOpenCV::tree() {
	m_treeData = cv::ml::RTrees::create();
	m_treeData->setPriors(cv::Mat());
	m_treeData->train(m_trainData);
}
//===============================================
void GOpenCV::maxDepth(int _maxDepth) {
	m_treeData->setMaxDepth(_maxDepth);
}
//===============================================
void GOpenCV::minSample(int _minSample) {
	m_treeData->setMinSampleCount(_minSample);
}
//===============================================
void GOpenCV::accuracy(float _accuracy) {
	m_treeData->setRegressionAccuracy(_accuracy);
}
//===============================================
void GOpenCV::surrogates(bool _surrogates) {
	m_treeData->setUseSurrogates(_surrogates);
}
//===============================================
void GOpenCV::maxCategories(int _maxCategories) {
	m_treeData->setMaxCategories(_maxCategories);
}
//===============================================
void GOpenCV::folds(int _folds) {
	m_treeData->setCVFolds(_folds);
}
//===============================================
void GOpenCV::rule(bool _rule) {
	m_treeData->setUse1SERule(_rule);
}
//===============================================
void GOpenCV::truncate(bool _truncate) {
	m_treeData->setTruncatePrunedTree(_truncate);
}
//===============================================
void GOpenCV::error(bool _test) {
	m_performance = m_treeData->calcError(m_trainData, _test, m_results);
}
//===============================================
void GOpenCV::names() {
	m_trainData->getNames(m_names);
}
//===============================================
void GOpenCV::falgs() {
	m_falgs = m_trainData->getVarSymbolFlags();
}
//===============================================
void GOpenCV::responses() {
	cv::Mat lResponses = m_trainData->getResponses();
	m_good = 0, m_bad = 0, m_total = 0;
	for (int i = 0; i < m_trainData->getNTrainSamples(); ++i) {
		float lReceived = m_results.at<float>(i, 0);
		float lExpected = lResponses.at<float>(i, 0);
		cv::String lReceivedName = m_names[(int)lReceived];
		cv::String lExpectedName = m_names[(int)lExpected];
		std::cout << "Received: " << lReceivedName << ", Expected: " << lExpectedName << std::endl;
		if(lReceived == lExpected) {
			m_good++;
		}
		else {
			m_bad++;
		}
		m_total++;
	}
}
//===============================================
void GOpenCV::names() {
	m_trainData->getNames(m_names);
}
//===============================================
void GOpenCV::names() {
	m_trainData->getNames(m_names);
}
//===============================================
void GOpenCV::names() {
	m_trainData->getNames(m_names);
}
//===============================================
void GOpenCV::priors(int _rows, int _cols, float* _priors) {
	m_priors = cv::Mat(_rows, _cols, CV_32F, _priors);
}
//===============================================
int GOpenCV::samples() const {
	return m_trainData->getNSamples();
}
//===============================================
void GOpenCV::print() const {
	std::cout << "Samples      : " << m_trainData->getNSamples() << "\n";
	std::cout << "TrainSamples : " << m_trainData->getNTrainSamples() << "\n";
	std::cout << "TestSamples  : " << m_trainData->getNTestSamples() << "\n";
}
//===============================================
void GOpenCV::split() {
	m_trainData->setTrainTestSplitRatio(m_ratio, false);
}
//===============================================
void GOpenCV::headerLine(int _headerLine) {
	m_headerLine = _headerLine;
}
//===============================================
void GOpenCV::startIndex(int _startIndex) {
	m_startIndex = _startIndex;
}
//===============================================
void GOpenCV::endIndex(int _endIndex) {
	m_endIndex = _endIndex;
}
//===============================================
void GOpenCV::specType(int _specType) {
	m_specType = _specType;
}
//===============================================
