//===============================================
#include "GQtMdi.h"
#include "GQtXml.h"
#include "GQtLog.h"
#include "GQtMdiChild.h"
//===============================================
GQtMdi::GQtMdi(QWidget* _parent) :
GQtMainWindow(_parent) {
    createDoms();
    createActions();
    createStatusBar();
    createCentralWidget();
    setRecentFilesVisible(hasRecentFiles());
    updateMenus();

    setWindowTitle(getTitle());
    setWindowIcon(QIcon(GQTRES("studio/img", getLogo())));
    resize(getWidth(), getHeight());
    setUnifiedTitleAndToolBarOnMac(true);

    GQTLOG->showErrorQt(this);
}
//===============================================
GQtMdi::~GQtMdi() {

}
//===============================================
void GQtMdi::createDoms() {
    m_dom.reset(new GQtXml);
    m_dom->loadXmlFile(GQTRES("studio/xml", "mdi.xml"));
    m_domData.reset(new GQtXml);
    m_domData->loadXmlFile(GQTRES("studio/xml", "mdi_data.xml"));
    m_domWord.reset(new GQtXml);
    m_domWord->loadXmlFile(GQTRES("studio/xml", "mdi_words.xml"));
}
//===============================================
void GQtMdi::createCentralWidget() {
    m_mdiArea = new QMdiArea;
    m_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(m_mdiArea);
    connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(onMdiAreaSubWindow(QMdiSubWindow*)));
}
//===============================================
GQtMdiChild* GQtMdi::createMdiChild() {
    GQtMdiChild* lChild = new GQtMdiChild;
    m_mdiArea->addSubWindow(lChild);

#ifndef QT_NO_CLIPBOARD
    QAction* lCutAction = getKeyAction("edit/cut");
    QAction* lCopyAction = getKeyAction("edit/copy");

    connect(lChild, SIGNAL(copyAvailable(bool)), lCutAction, SLOT(setEnabled(bool)));
    connect(lChild, SIGNAL(copyAvailable(bool)), lCopyAction, SLOT(setEnabled(bool)));
#endif

    return lChild;
}
//===============================================
void GQtMdi::writeSettings() {

}
//===============================================
bool GQtMdi::openFile(const QString& _filename) {
    if (QMdiSubWindow* existing = findMdiChild(_filename)) {
        m_mdiArea->setActiveSubWindow(existing);
        return true;
    }
    const bool succeeded = loadFile(_filename);
    if (succeeded) {
        statusBar()->showMessage(tr("Fichier chargé"), 2000);
    }
    return succeeded;
}
//===============================================
QMdiSubWindow* GQtMdi::findMdiChild(const QString& _filename) const {
    QString canonicalFilePath = QFileInfo(_filename).canonicalFilePath();
    const QList<QMdiSubWindow*> subWindows = m_mdiArea->subWindowList();
    for (QMdiSubWindow *window : subWindows) {
        GQtMdiChild* lChild = qobject_cast<GQtMdiChild*>(window->widget());
        if (lChild->currentFile() == canonicalFilePath) {
            return window;
        }
    }
    return 0;
}
//===============================================
bool GQtMdi::loadFile(const QString &_filename) {
    GQtMdiChild* lChild = createMdiChild();
    bool succeeded = lChild->loadFile(_filename);
    if (succeeded) {
        lChild->show();
    }
    else {
        lChild->close();
    }
    prependToRecentFiles(_filename);
    return succeeded;
}
//===============================================
GQtMdiChild* GQtMdi::activeMdiChild() const {
    if (QMdiSubWindow* activeSubWindow = m_mdiArea->activeSubWindow()) {
        return qobject_cast<GQtMdiChild*>(activeSubWindow->widget());
    }
    return 0;
}
//===============================================
void GQtMdi::updateMenus() {
    bool hasMdiChild = (activeMdiChild() != 0);

    QAction* lSaveAction = getKeyAction("file/save");
    QAction* lSaveAsAction = getKeyAction("file/saveas");

    lSaveAction->setEnabled(hasMdiChild);
    lSaveAsAction->setEnabled(hasMdiChild);

#ifndef QT_NO_CLIPBOARD
    QAction* lPasteAction = getKeyAction("edit/paste");
    lPasteAction->setEnabled(hasMdiChild);
#endif

    QAction* lClosection = getKeyAction("window/close");
    QAction* lCloseAllAction = getKeyAction("window/close/all");
    QAction* lTileAction = getKeyAction("window/tile");
    QAction* lCascadeAction = getKeyAction("window/cascade");
    QAction* lNextAction = getKeyAction("window/next");
    QAction* lPreviousAction = getKeyAction("window/previous");

    lClosection->setEnabled(hasMdiChild);
    lCloseAllAction->setEnabled(hasMdiChild);
    lTileAction->setEnabled(hasMdiChild);
    lCascadeAction->setEnabled(hasMdiChild);
    lNextAction->setEnabled(hasMdiChild);
    lPreviousAction->setEnabled(hasMdiChild);

#ifndef QT_NO_CLIPBOARD
    bool hasSelection = (activeMdiChild() && activeMdiChild()->textCursor().hasSelection());

    QAction* lCutAction = getKeyAction("edit/cut");
    QAction* lCopyAction = getKeyAction("edit/copy");

    lCutAction->setEnabled(hasSelection);
    lCopyAction->setEnabled(hasSelection);
#endif
}
//===============================================
void GQtMdi::closeEvent(QCloseEvent* event) {
    m_mdiArea->closeAllSubWindows();
    if (m_mdiArea->currentSubWindow()) {
        event->ignore();
    }
    else {
        writeSettings();
        event->accept();
    }
}
//===============================================
void GQtMdi::onMenuAction() {
    QAction* lAction = qobject_cast<QAction*>(sender());
    QString lKey = lAction->data().toString();
    qDebug() << lKey;

    // file
    if(lKey == "file/new") {
        GQtMdiChild* lChild = createMdiChild();
        lChild->newFile(getTitle());
        lChild->show();
    }
    else if(lKey == "file/open") {
        const QString lFilename = QFileDialog::getOpenFileName(this);
        if (!lFilename.isEmpty()) {
            openFile(lFilename);
        }
    }
    else if(lKey == "file/save") {
        if (activeMdiChild() && activeMdiChild()->save()) {
            statusBar()->showMessage(tr("Fichier sauvegardé"), 2000);
        }
    }
    else if(lKey == "file/saveas") {
        GQtMdiChild* lChild = activeMdiChild();
        if (lChild && lChild->saveAs()) {
            statusBar()->showMessage(tr("Fichier sauvegardé"), 2000);
            prependToRecentFiles(lChild->currentFile());
        }
    }
    else if(lKey == "file/switch/layout") {
        if (layoutDirection() == Qt::LeftToRight) {
            QGuiApplication::setLayoutDirection(Qt::RightToLeft);
        }
        else {
            QGuiApplication::setLayoutDirection(Qt::LeftToRight);
        }
    }
    else if(lKey == "file/exit") {
        qApp->closeAllWindows();
    }
    // edit
    else if(lKey == "edit/cut") {
        if (activeMdiChild()) {
            activeMdiChild()->cut();
        }
    }
    else if(lKey == "edit/copy") {
        if (activeMdiChild()) {
            activeMdiChild()->copy();
        }
    }
    else if(lKey == "edit/paste") {
        if (activeMdiChild()) {
            activeMdiChild()->paste();
        }
    }
    // window
    else if(lKey == "window/close") {
        m_mdiArea->closeActiveSubWindow();
    }
    else if(lKey == "window/close/all") {
        m_mdiArea->closeAllSubWindows();
    }
    else if(lKey == "window/tile") {
        m_mdiArea->tileSubWindows();
    }
    else if(lKey == "window/cascade") {
        m_mdiArea->cascadeSubWindows();
    }
    else if(lKey == "window/next") {
        m_mdiArea->activateNextSubWindow();
    }
    else if(lKey == "window/previous") {
        m_mdiArea->activatePreviousSubWindow();
    }
     // help
    else if(lKey == "help/app") {
        QString lTitle = getTitle();
        QString lMessage = getAbout().arg(lTitle);
        QMessageBox::about(this, lTitle, lMessage);
    }
    else if(lKey == "help/qt") {
        QApplication::aboutQt();
    }
}
//===============================================
void GQtMdi::onMenuBox() {
    QMenu* lMenu = qobject_cast<QMenu*>(sender());
    QString lKey = m_menuKey[lMenu];
    qDebug() << lKey;

    if(lKey == "file/recent") {
        updateRecentFiles();
    }
}
//===============================================
void GQtMdi::onMenuBoxAction() {
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
void GQtMdi::onMdiAreaSubWindow(QMdiSubWindow* _subWindow) {
    updateMenus();
}
//===============================================
