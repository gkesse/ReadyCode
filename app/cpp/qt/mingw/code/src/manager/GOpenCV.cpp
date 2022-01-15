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
int GOpenCV::m_winnameId = 1;
std::map<int, GOpenCV*> GOpenCV::m_opencvMap;
//===============================================
GOpenCV::GOpenCV() : GObject() {
    createDoms();
}
//===============================================
GOpenCV::~GOpenCV() {

}
//===============================================
GOpenCV* GOpenCV::Instance() {
    if(m_instance == 0) {
        m_instance = new GOpenCV;
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
GOpenCV& GOpenCV::closeWindow() {
    cv::destroyWindow(m_winname);
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
GOpenCV& GOpenCV::loadImage(const std::string& _filename) {
    m_img = cv::imread(_filename, cv::IMREAD_COLOR);
    return *this;
}
//===============================================
void GOpenCV::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("cpp/xml", "opencv.xml"));
    m_dom->createXPath();
    m_domData.reset(new GXml);
    m_domData->loadXmlFile(GRES("cpp/xml", "opencv_data.xml"));
    m_domData->createXPath();
}
//===============================================
std::string GOpenCV::getTitle() const {
    m_dom->queryXPath("/rdv/opencv/settings/setting[name='window']/title");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData + " (" + std::to_string(GOpenCV::m_winnameId) + ")";
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
void GOpenCV::createOpenCV() {
    initDom();
    m_dom->queryXPath("/rdv");
    m_dom->getNodeXPath();
    m_dom->appendNode("opencv");
}
//===============================================
void GOpenCV::addWindowId(int _id) {
    m_dom->queryXPath("/rdv/opencv");
    m_dom->getNodeXPath();
    m_dom->appendNode("id", std::to_string(_id));
}
//===============================================
void GOpenCV::addWindowIName(const std::string& _winname) {
    m_dom->queryXPath("/rdv/opencv");
    m_dom->getNodeXPath();
    m_dom->appendNode("winname", _winname);
}
//===============================================
void GOpenCV::saveWindowId(int _id) {
    m_domData->queryXPath("/rdv/datas/data[code='opencv/window/id']/map");
    m_domData->getNodeXPath();
    GXml lNode;
    lNode.createNode("data");
    lNode.appendNode("id", std::to_string(_id));
    m_domData->appendNode(lNode);
    m_domData->saveXmlFile();
}
//===============================================
void GOpenCV::clearWindowId() {
    m_domData->queryXPath("/rdv/datas/data[code='opencv/window/id']/map/data");
    m_domData->getNodeXPath();
    m_domData->clearNodeXPath();
    m_domData->saveXmlFile();
}
//===============================================
void GOpenCV::incWindowId() {
    GOpenCV::m_winnameId++;
}
//===============================================
int GOpenCV::getWindowId() const {
    return GOpenCV::m_winnameId;
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
    else if(lMethod == "clear_window_id") {
        onClearWindowId(_request, _client);
    }
    else if(lMethod == "open_image_file") {
        onOpenImageFile(_request, _client);
    }
    else {
        onUnknownMethod(_request, _client);
    }
}
//===============================================
void GOpenCV::addModule(int _id, GOpenCV* _opencv) {
    GOpenCV::m_opencvMap[_id] = _opencv;
}
//===============================================
GOpenCV* GOpenCV::getModule(int _id) {
    return GOpenCV::m_opencvMap[_id];
}
//===============================================
int GOpenCV::countModule() const {
    return GOpenCV::m_opencvMap.size();
}
//===============================================
bool GOpenCV::hasModule() const {
    return (countModule() != 0);
}
//===============================================
bool GOpenCV::hasModule(int _id) {
    std::map<int, GOpenCV*>::iterator it;
    for (it = GOpenCV::m_opencvMap.begin(); it != GOpenCV::m_opencvMap.end(); it++) {
        int lModuleId = it->first;
        if(lModuleId == _id) return true;
    }
    return false;
}
//===============================================
void GOpenCV::onRunOpenCV(GObject* _request, GSocket* _client) {
    GOpenCV* lOpenCV = new GOpenCV;
    lOpenCV->m_request = _request;
    lOpenCV->m_client = _client;

    GOpenCV lDom;
    lDom.createOpenCV();
    lDom.addWindowId(getWindowId());
    lDom.addWindowIName(getTitle());
    _client->addDataOut(lDom);

    saveWindowId(getWindowId());

    addModule(getWindowId(), lOpenCV);

    GThread lThread;
    lThread.createThread(onRunOpenCVThread, lOpenCV);
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

    lOpenCV->incWindowId();

    while(1) {
        lOpenCV->showImage(*lOpenCV);
        if(lOpenCV->waitKey(lWiatKey) == 'q') break;
    }

    lOpenCV->closeWindow();
    delete lOpenCV;
    return 0;
}
//===============================================
void GOpenCV::onClearWindowId(GObject* _request, GSocket* _client) {
    GOpenCV lDom;
    lDom.clearWindowId();
}
//===============================================
void GOpenCV::onOpenImageFile(GObject* _request, GSocket* _client) {
    if(!hasModule()) return;
    int lModuleId = 1;
    std::string lImageFile = GRES("img", "fruits.jpg");
    GOpenCV* lOpenCV = GOPENCV->getModule(lModuleId);
    lOpenCV->loadImage(lImageFile);
}
//===============================================
void GOpenCV::onUnknownMethod(GObject* _request, GSocket* _client) {
    std::string lModule = _request->getModule();
    std::string lMethod = _request->getMethod();
    GOpenCV* lDataOut = new GOpenCV;
    lDataOut->createError();
    lDataOut->addErrorMsg(sformat("Erreur la methode (%s) "
            "du module (%s) n'existe pas.", lMethod.c_str(), lModule.c_str()));
    _client->addDataOut(lDataOut);
    delete lDataOut;
}
//===============================================
