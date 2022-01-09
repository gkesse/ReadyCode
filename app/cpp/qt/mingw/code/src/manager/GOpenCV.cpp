//===============================================
#include "GOpenCV.h"
#include "GSocket.h"
#include "GThread.h"
#include "GTimer.h"
#include "GString.h"
#include "GXml.h"
//===============================================
GOpenCV* GOpenCV::m_instance = 0;
//===============================================
GOpenCV::GOpenCV(bool _init) : GObject() {
    if(_init) {
        createDoms();
    }
}
//===============================================
GOpenCV::~GOpenCV() {

}
//===============================================
GOpenCV* GOpenCV::Instance() {
    if(m_instance == 0) {
        m_instance = new GOpenCV(true);
    }
    return m_instance;
}
//===============================================
void GOpenCV::run(int _argc, char** _argv) {
    int lWiatKey = getWaitKey();

    GOpenCV lOpenCV;
    lOpenCV.createWindow(getTitle(), 1);
    lOpenCV.createImageRgb(getWidth(), getHeight(), getBgColor());

    while(1) {
        lOpenCV.showImage(lOpenCV);
        if(lOpenCV.waitKey(lWiatKey) == 'q') break;
    }
}
//===============================================
GOpenCV& GOpenCV::createWindow(const std::string& _winname, int _flags) {
    cv::namedWindow(_winname, _flags);
    m_winname = _winname;
    return *this;
}
//===============================================
int GOpenCV::waitKey(int _ms) {
    int lKey = cv::waitKey(_ms);
    return lKey;
}
//===============================================
GOpenCV& GOpenCV::createImage(int _width, int _height, int _type, const cv::Scalar& _color) {
    m_img = cv::Mat(_height, _width, _type, _color);
    return *this;
}
//===============================================
GOpenCV& GOpenCV::createImageRgb(int _width, int _height, const cv::Scalar& _color) {
    m_img = cv::Mat(_height, _width, CV_8UC3, _color);
    return *this;
}
//===============================================
GOpenCV& GOpenCV::showImage(GOpenCV& _img) {
    cv::imshow(m_winname, _img.m_img);
    return *this;
}
//===============================================
void GOpenCV::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("cpp/xml", "opencv.xml"));
    m_dom->createXPath();
}
//===============================================
std::string GOpenCV::getTitle() const {
    m_dom->queryXPath("/rdv/opencv/settings/setting[name='window']/title");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GOpenCV::getWidth() const {
    m_dom->queryXPath("/rdv/opencv/settings/setting[name='window']/width");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return std::stoi(lData);
}
//===============================================
int GOpenCV::getHeight() const {
    m_dom->queryXPath("/rdv/opencv/settings/setting[name='window']/height");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return std::stoi(lData);
}
//===============================================
int GOpenCV::getWaitKey() const {
    m_dom->queryXPath("/rdv/opencv/settings/setting[name='window']/waitkey");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return std::stoi(lData);
}
//===============================================
cv::Scalar GOpenCV::getBgColor() const {
    m_dom->queryXPath("/rdv/opencv/settings/setting[name='window']/bgcolor");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return GString(lData).getRgb();
}
//===============================================
int GOpenCV::getTimer() const {
    m_dom->queryXPath("/rdv/opencv/settings/setting[name='server']/timer");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return std::stoi(lData);
}
//===============================================
void CALLBACK GOpenCV::onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
    std::queue<std::string>& lDataIn = GSOCKET->getDataIn();
    std::queue<GSocket*>& lClientIn = GSOCKET->getClientIn();

    if(!lDataIn.empty()) {
        std::string lData = lDataIn.front();
        GSocket* lClient = lClientIn.front();

        lDataIn.pop();
        lClientIn.pop();

        GSOCKET->showMessage(lData);

        lClient->sendResponse();
    }
}
//===============================================
void GOpenCV::onModule(GObject* _request, GSocket* _client) {
    std::string lMethod = _request->getMethod();
    if(lMethod == "run_opencv") {
        onRunOpenCV(_request, _client);
    }
}
//===============================================
void GOpenCV::onRunOpenCV(GObject* _request, GSocket* _client) {
    GOPENCV->m_request = _request;
    GOPENCV->m_client = _client;
    GTHREAD->createThread(onRunOpenCVThread, GOPENCV);
}
//===============================================
DWORD WINAPI GOpenCV::onRunOpenCVThread(LPVOID _params) {
    GOpenCV* lOpenCV = (GOpenCV*)_params;

    int lWiatKey = lOpenCV->getWaitKey();
    int lWidth = lOpenCV->getWidth();
    int lHeight = lOpenCV->getHeight();
    std::string lTitle = lOpenCV->getTitle();
    cv::Scalar lBgColor = lOpenCV->getBgColor();

    lOpenCV->createWindow(lTitle, 1);
    lOpenCV->createImageRgb(lWidth, lHeight, lBgColor);

    while(1) {
        lOpenCV->showImage(*lOpenCV);
        if(lOpenCV->waitKey(lWiatKey) == 'q') break;
    }

    delete lOpenCV;
    lOpenCV = 0;
    return 0;
}
//===============================================
