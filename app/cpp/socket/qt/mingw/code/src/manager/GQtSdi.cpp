//===============================================
#include "GQtSdi.h"
#include "GQtXml.h"
#include "GQtResource.h"
#include "GQtLog.h"
//===============================================
int GQtSdi::m_documentCount = 1;
//===============================================
GQtSdi::GQtSdi(QWidget* _parent) :
GQtMainWindow(_parent) {
    createDoms();
    createActions();
    createCentralWidget();
    createWindowTitle();
    setWindowIcon(QIcon(GQTIMG(getLogo())));
    resize(getWidth(), getHeight());
    GQTLOG->showErrorQt(this);
}
//===============================================
GQtSdi::~GQtSdi() {

}
//===============================================
void GQtSdi::createDoms() {
    m_dom.reset(new GQtXml);
    m_dom->openFileRD(GQTXML("sdi.xml"));
    m_domData.reset(new GQtXml);
    m_domData->openFileRD(GQTXML("sdi_data.xml"));
}
//===============================================
void GQtSdi::createCentralWidget() {
    m_textEdit = new QTextEdit;
    setCentralWidget(m_textEdit);
    connect(m_textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(onTextEditChange()));
}
//===============================================
void GQtSdi::createWindowTitle(const QString& _filename) {
    QString lCurrentFile;
    bool lUntitled = (_filename == "");
    if (_filename == "") {
        lCurrentFile = QString("%1%2.%3").
                arg(getUntitledName()).
                arg(m_documentCount++).
                arg(getUntitledExtension());
    }
    else {
        lCurrentFile = QFileInfo(_filename).canonicalFilePath();
    }

    m_textEdit->document()->setModified(false);
    setWindowModified(false);

    if (!lUntitled && windowFilePath() != lCurrentFile) {
        prependToRecentFiles(lCurrentFile);
    }

    setWindowFilePath(lCurrentFile);

}
//===============================================
void GQtSdi::setPosition(QWidget* _parent) {
    if (!_parent) return;
    int topFrameWidth = _parent->geometry().top() - _parent->pos().y();
    if (!topFrameWidth) {
        topFrameWidth = 40;
    }
    const QPoint pos = _parent->pos() + 2 * QPoint(topFrameWidth, topFrameWidth);
    if (screen()->availableGeometry().contains(rect().bottomRight() + pos)) {
        move(pos);
    }
}
//===============================================
void GQtSdi::onMenuAction() {
    QAction* lAction = qobject_cast<QAction*>(sender());
    QString lKey = lAction->data().toString();
    qDebug() << lKey;

    if(lKey == "file/new") {
        GQtSdi* lSdiWindow = new GQtSdi;
        lSdiWindow->setWindowFlag(this);
        lSdiWindow->setPosition(this);
        lSdiWindow->show();
        lSdiWindow->activateWindow();
    }
    else if(lKey == "file/saveas") {
        prependToRecentFiles("Fichier3.txt");
    }
}
//===============================================
void GQtSdi::onTextEditChange() {

}
//===============================================
