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

    clearWindowId();

    GQTLOG->showErrorQt(this);
}
//===============================================
GQtOpenCVUi::~GQtOpenCVUi() {

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
void GQtOpenCVUi::createCentralWidget() {
    m_pageMap = new GQtStackWidget;
    setCentralWidget(createTestPage());

    m_pageMap->addWidget("test", createTestPage());
}
//===============================================
QWidget* GQtOpenCVUi::createTestPage() {
    QTextEdit* lTextEdit = new QTextEdit;
    m_objectMap[lTextEdit] = "test/page/textedit";

    QVBoxLayout* lButtonLayout = new QVBoxLayout;
    lButtonLayout->setAlignment(Qt::AlignTop);

    for(int i = 0; i < countTestPageButtons(); i++) {
        QPushButton* lButton = new QPushButton;
        QString lName = getTestPageButtonName(i);
        QString lKey = getTestPageButtonKey(i);
        lButton->setText(lName);
        lButtonLayout->addWidget(lButton);
        connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
        m_objectMap[lButton] = lKey;
    }

    QHBoxLayout* lCenterLayout = new QHBoxLayout;
    lCenterLayout->addWidget(lTextEdit);
    lCenterLayout->addLayout(lButtonLayout);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lCenterLayout);

    QFrame* lMainWidget = new QFrame;
    lMainWidget->setLayout(lMainLayout);

    return lMainWidget;
}
//===============================================
int GQtOpenCVUi::countTestPageButtons() const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='test/page/buttons']/map/button"));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
QString GQtOpenCVUi::getTestPageButtonName(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='test/page/buttons']/map/button[position()=%1]/name").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtOpenCVUi::getTestPageButtonKey(int _index) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='test/page/buttons']/map/button[position()=%1]/key").arg(_index + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtOpenCVUi::getTestPageXmlFilename() const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='test/page/xml/filename']/filename"));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
std::string GQtOpenCVUi::sendTestMessage() {
    QTextEdit* lTextEdit = qobject_cast<QTextEdit*>(getObject("test/page/textedit"));
    QString lDataIn = lTextEdit->toPlainText();
    if(lDataIn == "") {
        m_requestDom.reset(new GObject);
        m_requestDom->createError();
        m_requestDom->addErrorMsg("Erreur la methode (sendTestMessage) a echoue.");
        return m_requestDom->toString();
    }
    std::string lDataOut;
    GSOCKET->callServerTcp(lDataIn.toStdString(), lDataOut);
    return lDataOut;
}
//===============================================
std::string GQtOpenCVUi::loadTestMessage() {
    QTextEdit* lTextEdit = qobject_cast<QTextEdit*>(getObject("test/page/textedit"));
    QString lFilename = getTestPageXmlFilename();
    QFile lFile(lFilename);
    if (!lFile.open(QFile::ReadOnly | QFile::Text)) {
        m_requestDom.reset(new GObject);
        m_requestDom->createError();
        m_requestDom->addErrorMsg(GOBJECT->sformat("Erreur la methode (loadTestMessage) a echoue "
                "sur le fichier (%s).", lFilename.toStdString().c_str()));
        return m_requestDom->toString();
    }
    QTextStream in(&lFile);
    QString lDataIn = in.readAll();
    lFile.close();
    lTextEdit->setText(lDataIn);
    std::string lDataOut;
    GSOCKET->callServerTcp(lDataIn.toStdString(), lDataOut);
    return lDataOut;
}
//===============================================
std::string GQtOpenCVUi::clearXmlMessage() {
    std::string lDataOut;
    m_requestDom.reset(new GObject);
    m_requestDom->createRequest("opencv", "clear_xml_messages");
    GSOCKET->callServerTcp(m_requestDom->toString(), lDataOut);
    return lDataOut;
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
    std::string lDataOut;

    if(lKey == "server/stop") {
        lDataOut = stopServer();
    }
    //
    else if(lKey == "opencv/run") {
        lDataOut = runOpenCV();
    }
    else if(lKey == "opencv/stop") {
        lDataOut = stopOpenCV();
    }
    //
    else if(lKey == "image/open/file") {
        lDataOut = openImageFile();
    }

    showDebug(lDataOut);
    GQTLOG->addErrorIn(lDataOut);
    GQTLOG->showErrorQt(this);
}
//===============================================
void GQtOpenCVUi::onEvent() {
    QString lKey = m_objectMap[sender()];
    showDebug(lKey);
    std::string lDataOut;

    if(lKey == "test/page/button/send") {
        lDataOut = sendTestMessage();
    }
    else if(lKey == "test/page/button/load") {
        lDataOut = loadTestMessage();
    }
    else if(lKey == "test/page/button/clear") {
        lDataOut = loadTestMessage();
    }

    showDebug(lDataOut);
    GQTLOG->addErrorIn(lDataOut);
    GQTLOG->showErrorQt(this);
}
//===============================================
std::string GQtOpenCVUi::stopServer() {
    std::string lDataOut;
    m_requestDom.reset(new GObject);
    m_requestDom->createRequest("server", "stop_server");
    GSOCKET->callServerTcp(m_requestDom->toString(), lDataOut);
    return lDataOut;
}
//===============================================
std::string GQtOpenCVUi::runOpenCV() {
    std::string lDataOut;
    m_requestDom.reset(new GObject);
    m_requestDom->createRequest("opencv", "run_opencv");
    GSOCKET->callServerTcp(m_requestDom->toString(), lDataOut);
    return lDataOut;
}
//===============================================
std::string GQtOpenCVUi::stopOpenCV() {
    std::string lDataOut;
    return lDataOut;
}
//===============================================
std::string GQtOpenCVUi::clearWindowId() {
    std::string lDataOut;
    m_requestDom.reset(new GObject);
    m_requestDom->createRequest("opencv", "clear_window_id");
    GSOCKET->callServerTcp(m_requestDom->toString(), lDataOut);
    return lDataOut;
}
//===============================================
std::string GQtOpenCVUi::openImageFile() {
    std::string lDataOut;
    m_requestDom.reset(new GOpenCV);
    m_requestDom->createRequest("opencv", "open_image_file");
    GSOCKET->callServerTcp(m_requestDom->toString(), lDataOut);
    return lDataOut;
}
//===============================================
