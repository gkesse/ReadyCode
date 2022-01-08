//===============================================
#include "GQtOpenCVUi.h"
#include "GOpenCV.h"
#include "GSocket.h"
#include "GQtXml.h"
#include "GQtObject.h"
#include "GQtLog.h"
//===============================================
GQtOpenCVUi::GQtOpenCVUi(QWidget* _parent) :
GQtMainWindow(_parent) {
    createDoms();
    createActions();
    createCentralWidget();

    restoreGeometry(getGeometry());

    setWindowTitle(getTitle());
    setWindowIcon(QIcon(GQTRES("studio/img", getLogo())));
    resize(getWidth(), getHeight());
    setUnifiedTitleAndToolBarOnMac(true);

    GQTLOG->showErrorQt(this);
}
//===============================================
GQtOpenCVUi::~GQtOpenCVUi() {

}
//===============================================
void GQtOpenCVUi::createCentralWidget() {

}
//===============================================
void GQtOpenCVUi::createDoms() {
    m_dom.reset(new GQtXml);
    m_dom->loadXmlFile(GQTRES("studio/xml", "opencv_ui.xml"));
    m_dom->createXPath();
    m_domData.reset(new GQtXml);
    m_domData->loadXmlFile(GQTRES("studio/xml", "opencv_ui_data.xml"));
    m_domData->createXPath();
    m_domWord.reset(new GQtXml);
    m_domWord->loadXmlFile(GQTRES("studio/xml", "opencv_ui_words.xml"));
    m_domWord->createXPath();
}
//===============================================
void GQtOpenCVUi::closeEvent(QCloseEvent *event) {
    writeGeometry(saveGeometry());
}
//===============================================
void GQtOpenCVUi::onMenuAction(bool _checked) {
    QAction* lAction = qobject_cast<QAction*>(sender());
    QString lKey = lAction->data().toString();
    showDebug(lKey);

    if(lKey == "opencv/run") {
        runOpenCV();
    }
    else if(lKey == "opencv/stop") {
        stopOpenCV();
    }

    GQTLOG->showErrorQt(this);
}
//===============================================
void GQtOpenCVUi::runOpenCV() {
    GObject lRequest;
    lRequest.initDom("opencv", "run_opencv");

    std::string lDataIn = lRequest.toString();
    std::string lDataOut;
    GSOCKET->callServerTcp(lDataIn, lDataOut);
    GQTLOG->addErrorIn(lDataOut.c_str());
    showDebug(lDataOut.c_str());
}
//===============================================
void GQtOpenCVUi::stopOpenCV() {

}
//===============================================
