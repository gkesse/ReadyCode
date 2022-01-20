//===============================================
#include "GQtOpenCVUi.h"
#include "GQtStackWidget.h"
#include "GOpenCV.h"
#include "GRequest.h"
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

    showDebug(clearWindowId());

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

    lTextEdit->setStyleSheet(QString(""
            "QTextEdit {"
            "background-color: #111111;"
            "color: #ffffff;"
            "font-family: courier new;"
            "font-size: 14px;"
            "font-weight: bold;"
            "padding: 10px;"
            "}"
            ""));

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

    QTabWidget* lTabWidget = new QTabWidget;
    m_objectMap[lTabWidget] = "test/page/tabwidget";

    lTabWidget->addTab(lTextEdit, "Editer");
    lTabWidget->addTab(createTestLoadPage(), "Charger");

    QHBoxLayout* lCenterLayout = new QHBoxLayout;
    lCenterLayout->addWidget(lTabWidget);
    lCenterLayout->addLayout(lButtonLayout);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lCenterLayout);

    QFrame* lMainWidget = new QFrame;
    lMainWidget->setLayout(lMainLayout);

    return lMainWidget;
}
//===============================================
QWidget* GQtOpenCVUi::createTestLoadPage() {
    QTreeWidget* lTreeWidget = new QTreeWidget;
    m_objectMap[lTreeWidget] = "test/page/load/xml/messages";

    lTreeWidget->setHeaderLabels(QStringList() << "ID" << "Méthode");

    std::string lXmlMessage = loadXmlMessage();

    GRequest lRequest;
    lRequest.loadDom(lXmlMessage);
    showDebug(lRequest);

    std::vector<std::string> lModules = lRequest.loadXmlModules();

    for(size_t i = 0; i < lModules.size(); i++) {
        std::string lModule = lModules.at(i);
        QTreeWidgetItem* lRoot = new QTreeWidgetItem(lTreeWidget);
        lRoot->setText(0, lModule.c_str());
        std::vector<GRequest> lReqs = lRequest.loadRequests(lModule);

        for(size_t j = 0; j < lReqs.size(); j++) {
            GRequest lReq = lReqs.at(j);
            QTreeWidgetItem* lChild = new QTreeWidgetItem();
            lChild->setData(2, Qt::EditRole, lReq.getMessage().c_str());
            lChild->setText(0, lReq.getId().c_str());
            lChild->setText(1, lReq.getMethod().c_str());
            lRoot->addChild(lChild);
        }
    }

    QHBoxLayout* lCenterLayout = new QHBoxLayout;
    lCenterLayout->addWidget(lTreeWidget);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lCenterLayout);

    QFrame* lMainWidget = new QFrame;
    lMainWidget->setLayout(lMainLayout);

    connect(lTreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onEvent(QTreeWidgetItem*, int)));

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
    std::string lDataIn = lTextEdit->toPlainText().toStdString();
    if(lDataIn == "") {
        GObject lRequest;
        lRequest.initError();
        lRequest.addErrorMsg("Erreur l'editeur de text est vide.");
        return lRequest.toString();
    }
    std::string lDataOut;
    GSOCKET->callServerTcp(lDataIn, lDataOut);
    return lDataOut;
}
//===============================================
std::string GQtOpenCVUi::loadTestMessage() {
    QTextEdit* lTextEdit = qobject_cast<QTextEdit*>(getObject("test/page/textedit"));
    QString lFilename = getTestPageXmlFilename();
    QFile lFile(lFilename);
    if (!lFile.open(QFile::ReadOnly | QFile::Text)) {
        GOpenCV lRequest;
        lRequest.initError();
        lRequest.addErrorMsg(GOBJECT->sformat("Erreur la methode (loadTestMessage) a echoue "
                "sur le fichier (%s).", lFilename.toStdString().c_str()));
        return lRequest.toString();
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
    GObject lRequest;
    lRequest.initRequest("opencv", "clear_xml_messages");
    GSOCKET->callServerTcp(lRequest, lDataOut);
    return lDataOut;
}
//===============================================
std::string GQtOpenCVUi::loadXmlMessage() {
    std::string lDataOut;
    GObject lRequest;
    lRequest.initRequest("master", "load_xml_messages");
    GSOCKET->callServerTcp(lRequest, lDataOut);
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

    if(lKey == "master/server/stop") {
        lDataOut = stopMasterServer();
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
void GQtOpenCVUi::onEvent(QTreeWidgetItem* _item, int _column) {
    QString lKey = m_objectMap[sender()];
    showDebug(lKey);
    QTreeWidgetItem* lParent = _item->parent();

    if(lKey == "test/page/load/xml/messages") {
        if(lParent) {
            QString lId = _item->data(0, Qt::EditRole).toString();
            QString lModule = lParent->data(0, Qt::EditRole).toString();
            QString lMethod = _item->data(1, Qt::EditRole).toString();
            QString lMessage = _item->data(2, Qt::EditRole).toString();
            GRequest lReq;
            lReq.setId(lId.toStdString());
            lReq.setModule(lModule.toStdString());
            lReq.setMethod(lMethod.toStdString());
            lReq.setMessage(lMessage.toStdString());
            onLoadXmlMessage(lReq);
        }
    }
}
//===============================================
std::string GQtOpenCVUi::stopMasterServer() {
    std::string lDataOut;
    GObject lRequest;
    lRequest.initRequest("master", "stop_server");
    GSOCKET->callServerTcp(lRequest, lDataOut);
    return lDataOut;
}
//===============================================
std::string GQtOpenCVUi::runOpenCV() {
    std::string lDataOut;
    GOpenCV lRequest;
    lRequest.initRequest("opencv", "run_opencv");
    GSOCKET->callServerTcp(lRequest.toString(), lDataOut);
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
    GOpenCV lRequest;
    lRequest.initRequest("opencv", "clear_window_id");
    GSOCKET->callServerTcp(lRequest.toString(), lDataOut);
    return lDataOut;
}
//===============================================
std::string GQtOpenCVUi::openImageFile() {
    std::string lDataOut;
    GOpenCV lRequest;
    lRequest.initRequest("opencv", "open_image_file");
    GSOCKET->callServerTcp(lRequest, lDataOut);
    return lDataOut;
}
//===============================================
void GQtOpenCVUi::onLoadXmlMessage(const GRequest& _req) {
    QTabWidget* lTabWidget = qobject_cast<QTabWidget*>(getObject("test/page/tabwidget"));
    QTextEdit* lTextEdit = qobject_cast<QTextEdit*>(getObject("test/page/textedit"));
    lTextEdit->setPlainText(_req.getMessage().c_str());
    lTabWidget->setCurrentIndex(0);
}
//===============================================
