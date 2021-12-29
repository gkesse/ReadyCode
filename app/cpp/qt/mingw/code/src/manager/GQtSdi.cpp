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
    m_untitled = true;

    createDoms();
    createActions();
    createStatusBar();
    createCentralWidget();
    createClipboard();
    setRecentFilesVisible(hasRecentFiles());
    setCurrentFile();

    setWindowIcon(QIcon(GQTIMG(getLogo())));
    resize(getWidth(), getHeight());
    setUnifiedTitleAndToolBarOnMac(true);

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
    m_domWord.reset(new GQtXml);
    m_domWord->openFileRD(GQTXML("sdi_words.xml"));
}
//===============================================
void GQtSdi::createCentralWidget() {
    m_textEdit = new QTextEdit;
    setCentralWidget(m_textEdit);
    connect(m_textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(onTextEditChange()));
}
//===============================================
void GQtSdi::createClipboard() {
#ifndef QT_NO_CLIPBOARD
    QAction* lCutAction = getKeyAction("edit/cut");
    QAction* lCopyAction = getKeyAction("edit/copy");
    lCutAction->setEnabled(false);
    lCopyAction->setEnabled(false);
    connect(m_textEdit, SIGNAL(copyAvailable(bool)), lCutAction, SLOT(setEnabled(bool)));
    connect(m_textEdit, SIGNAL(copyAvailable(bool)), lCopyAction, SLOT(setEnabled(bool)));
#endif
}
//===============================================
void GQtSdi::setCurrentFile(const QString& _filename) {
    m_untitled = (_filename == "");
    if (m_untitled) {
        m_currentFile = QString("%1%2.%3").
                arg(getUntitledName()).
                arg(m_documentCount++).
                arg(getUntitledExtension());
    }
    else {
        m_currentFile = QFileInfo(_filename).canonicalFilePath();
    }

    m_textEdit->document()->setModified(false);
    setWindowModified(false);

    if (!m_untitled && windowFilePath() != m_currentFile) {
        prependToRecentFiles(m_currentFile);
    }

    createWindowTitle();
    setWindowFilePath(m_currentFile);
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
void GQtSdi::createWindowTitle() {
    QString lTitle = QString("%1 - %2[*]").
            arg(getTitle()).
            arg(strippedName(m_currentFile));
    setWindowTitle(lTitle);
}
//===============================================
void GQtSdi::openFile(const QString& _filename) {
    GQtSdi* existing = findMainWindow(_filename);
    if (existing) {
        existing->show();
        existing->raise();
        existing->activateWindow();
        return;
    }

    if (m_untitled && m_textEdit->document()->isEmpty() && !isWindowModified()) {
        loadFile(_filename);
        return;
    }

    GQtSdi* other = new GQtSdi;
    other->loadFile(_filename);
    if (other->m_untitled) {
        delete other;
        return;
    }
    other->show();
}
//===============================================
GQtSdi* GQtSdi::findMainWindow(const QString& _filename) const {
    QString canonicalFilePath = QFileInfo(_filename).canonicalFilePath();

    const QList<QWidget*> topLevelWidgets = QApplication::topLevelWidgets();
    for (QWidget *widget : topLevelWidgets) {
        GQtSdi* mainWin = qobject_cast<GQtSdi*>(widget);
        if (mainWin && mainWin->m_currentFile == canonicalFilePath) {
            return mainWin;
        }
    }

    return 0;
}
//===============================================
void GQtSdi::loadFile(const QString& _filename) {
    QFile file(_filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        GQTLOG->addError(QString("Erreur la methode (loadFile) a echoue\n"
                "sur le noeud (%1).").arg(_filename));
        return;
    }

    QTextStream in(&file);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    m_textEdit->setPlainText(in.readAll());
    QGuiApplication::restoreOverrideCursor();

    setCurrentFile(_filename);
    statusBar()->showMessage(tr("Le fichier a été chargé"), 2000);
}
//===============================================
bool GQtSdi::saveFile(const QString& _filename) {
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile lFile(_filename);
    if(lFile.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&lFile);
        out << m_textEdit->toPlainText();
        if (!lFile.commit()) {
            GQTLOG->addError(QString("Erreur la methode (saveFile) a echoue\n"
                    "sur le fichier (%1) (1).").arg(_filename));
            return false;
        }
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (saveFile) a echoue\n"
                "sur le fichier (%1) (2).").arg(_filename));
        return false;
    }
    QGuiApplication::restoreOverrideCursor();

    setCurrentFile(_filename);
    statusBar()->showMessage(tr("Le fichier a été sauvegardé"), 2000);
    return true;
}
//===============================================
bool GQtSdi::save() {
    if(m_untitled) {
        return saveAs();
    }
    else {
        return saveFile(m_currentFile);
    }
}
//===============================================
bool GQtSdi::saveAs() {
    QString lTitle = "Enregistrer sous";
    QString lFilename = QFileDialog::getSaveFileName(this, lTitle, m_currentFile);
    if (lFilename.isEmpty()) return false;
    return saveFile(lFilename);
}
//===============================================
bool GQtSdi::maybeSave() {
    if (!m_textEdit->document()->isModified()) {
        return true;
    }
    int lAnswer = QMessageBox::warning(this, getTitle(),
            tr("Le document a été modifié.\n"
               "Voulez-vous sauvegarder les modifications ?"),
               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if(lAnswer == QMessageBox::Save) {
        return save();
    }
    if(lAnswer == QMessageBox::Cancel) {
        return false;
    }
    return true;
}
//===============================================
void GQtSdi::setLanguage(const QString& _lang) {
    m_domWord->getRoot("rdv").getNode("lang");
    m_domWord->setNodeValue(_lang);
    m_domWord->saveFile();
}
//===============================================
void GQtSdi::setLanguageIndex(const QString& _key) {
    // get index coords
    QString lKey = "help/language";
    QString lKeyI = QString("%1/index/i").arg(lKey);
    QString lKeyJ = QString("%1/index/j").arg(lKey);
    int i = m_keyInt[lKeyI];
    int j = m_keyInt[lKeyJ];
    // get index position
    int lIndex = 0;
    int lCount = countBoxMenus(i, j);
    for(int k = 0; k < lCount; k++) {
        QString lKeyMenu = getBoxMenuKey(i, j, k);
        if(lKeyMenu == _key) {
            lIndex = k;
            break;
        }
    }
    // set index
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", i).getNode("submenus");
    m_dom->getNodeItem("submenu", j).getNode("menu");
    m_dom->getNodeOrEmpty("index");
    m_dom->setNodeValue(QString("%1").arg(lIndex));
    // save dom
    m_dom->saveFile();

}
//===============================================
void GQtSdi::closeEvent(QCloseEvent* _event) {
    if(maybeSave()) {
        _event->accept();
    }
    else {
        _event->ignore();
    }
}
//===============================================
void GQtSdi::onMenuAction() {
    QAction* lAction = qobject_cast<QAction*>(sender());
    QString lKey = lAction->data().toString();
    qDebug() << lKey;

    // file
    if(lKey == "file/new") {
        GQtSdi* lSdiWindow = new GQtSdi;
        lSdiWindow->setWindowFlag(this);
        lSdiWindow->setPosition(this);
        lSdiWindow->show();
        lSdiWindow->activateWindow();
    }
    else if(lKey == "file/open") {
        const QString lFilename = QFileDialog::getOpenFileName(this);
        if (!lFilename.isEmpty()) {
            openFile(lFilename);
        }
    }
    else if(lKey == "file/save") {
        save();
    }
    else if(lKey == "file/saveas") {
        saveAs();
    }
    else if(lKey == "file/close") {
        close();
    }
    else if(lKey == "file/exit") {
        qApp->closeAllWindows();
    }
    // edit
    else if(lKey == "edit/cut") {
        m_textEdit->cut();
    }
    else if(lKey == "edit/copy") {
        m_textEdit->copy();
    }
    else if(lKey == "edit/paste") {
        m_textEdit->paste();
    }
    // help
    else if(lKey == "help/app") {
        QString lTitle = getTitle();
        QString lMessage = QString(""
                "<b>%1</b> est un projet permettant de montrer<br>"
                "comment construire une application d'interface<br>"
                "de document unique à l'aide de Qt.").arg(lTitle);
        QMessageBox::about(this, lTitle, lMessage);
    }
    else if(lKey == "help/qt") {
        QApplication::aboutQt();
    }
}
//===============================================
void GQtSdi::onMenuBox() {
    QMenu* lMenu = qobject_cast<QMenu*>(sender());
    QString lKey = m_menuKey[lMenu];
    qDebug() << lKey;

    if(lKey == "file/recent") {
        updateRecentFiles();
    }
}
//===============================================
void GQtSdi::onMenuBoxAction() {
    QAction* lAction = qobject_cast<QAction*>(sender());
    QString lKey = lAction->data().toString();
    qDebug() << lKey;

    if(lKey == "help/language/fr") {
        setLanguageIndex(lKey);
        setLanguage("fr");
    }
    else if(lKey == "help/language/en") {
        setLanguageIndex(lKey);
        setLanguage("en");
    }
}
//===============================================
void GQtSdi::onBoxRecentFile() {
    QAction* lAction = qobject_cast<QAction*>(sender());
    QString lFilename = lAction->data().toString();
    openFile(lFilename);
}
//===============================================
void GQtSdi::onTextEditChange() {
    setWindowModified(true);
}
//===============================================
