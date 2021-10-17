//===============================================
#ifndef _GOpenCV_
#define _GOpenCV_
//===============================================
#include "GInclude.h"
//===============================================
class GOpenCV {
public:
	GOpenCV();
	~GOpenCV();
	void filename(const std::string& _filename);
	void title(const std::string& _title);
	std::string title() const;
	cv::Mat& img();
	void window();
	void open();
	void load();
	int width() const;
	int width2() const;
	int height() const;
	int height2() const;
	void scaleFactor(double _scaleFactor);
	void minNeighbors(int _minNeighbors);
	void minSize(int _width, int _height);
	void maxSize(int _width, int _height);
	int frame() const;
	int frames() const;
	void trackbar(const std::string& _name, int* _pos, int _count, void* _params);
	void trackbar(const std::string& _name, int _pos);
	void onTrackbar(cv::TrackbarCallback _onTrackbar);
	void onTrackbar(int _pos, int& _run, int& _dontset);
	bool empty() const;
	void read();
	void show();
	void show(GOpenCV& _out);
	void show(const std::string& _title);
	void wait();
	bool wait(int _ms);
	bool wait(int _ms, int& _run);
	void gaussian(GOpenCV& _out);
	void pyramid(GOpenCV& _out);
	void cascade();
	void gray(GOpenCV& _out);
	void bgr(GOpenCV& _out);
	void resize(GOpenCV& _out, int _width, int _height);
	void resize(GOpenCV& _out, double _factor);
	void resize(double _factor);
	void equalize(GOpenCV& _out);
	void objects();
	void objects(cv::Scalar* _colors, int _n, double _scale);
	void objects(GOpenCV& _out, cv::Scalar* _colors, int _n, double _scale);
	int count() const;
	void train();
	void tree();
	void maxDepth(int _maxDepth);
	void minSample(int _minSample);
	void accuracy(float _accuracy);
	void surrogates(bool _surrogates);
	void maxCategories(int _maxCategories);
	void folds(int _folds);
	void rule(bool _rule);
	void truncate(bool _truncate);
	void performanceData();
	void performanceTest();
	void names();
	void falgs();
	void responses();
	void priors(int _rows, int _cols, float* _priors);
	int samples() const;
	void print() const;
	void split();
	void headerLine(int _headerLine);
	void startIndex(int _startIndex);
	void endIndex(int _endIndex);
	void specType(int _specType);

protected:
	static int m_count;
	std::string m_filename;
	std::string m_title;
	cv::VideoCapture m_cap;
	cv::Mat m_img;
	cv::TrackbarCallback m_onTrackbar;
	cv::Ptr<cv::CascadeClassifier> m_cascade;
	std::vector<cv::Rect> m_objects;
	cv::Size m_minSize;
	cv::Size m_maxSize;
	double m_scaleFactor;
	int m_minNeighbors;
	cv::Ptr<cv::ml::TrainData> m_trainData;
	cv::Ptr<cv::ml::RTrees> m_treeData;
	int m_headerLine;
	int m_startIndex;
	int m_endIndex;
	std::string m_specType;
	char m_delimiter;
	char m_missch;
	double m_ratio;
	cv::Mat m_priors;
	cv::Mat m_resultData;
	cv::Mat m_resultTest;
	float m_performanceData;
	float m_performanceTest;
	std::vector<cv::String> m_names;
	cv::Mat m_falgs;
	int m_good;
	int m_bad;
	int m_total;
};
//==============================================
#endif
//==============================================
