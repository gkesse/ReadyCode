//===============================================
#include "GQtSpreadWindow.h"
#include "GQtSpreadSheet.h"
#include "GResource.h"
#include "GQtLog.h"
//===============================================
GQtSpreadWindow::GQtSpreadWindow(QWidget* _parent) :
QMainWindow(_parent) {
    m_params.app_name = "ReadyApp-Spreadsheet";

    m_spreadsheet = new GQtSpreadSheet;
    setCentralWidget(m_spreadsheet);

    setWindowTitle(m_params.app_name);
    resize(m_params.width, m_params.height);

    createActions();
    createMenus();

    readSettings();
}
//===============================================
GQtSpreadWindow::~GQtSpreadWindow() {

}
//===============================================
void GQtSpreadWindow::createActions() {
    GQTLOG->showMsg(GMSG);

    // ficher
    m_newAction = new QAction(tr("&Nouveau"), this);
    m_newAction->setIcon(QIcon(GIMG("new.png")));
    m_newAction->setShortcut(QKeySequence::New);
    m_newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(m_newAction, SIGNAL(triggered()), this, SLOT(onNewFile()));

    m_openAction = new QAction(tr("&Ouvrir..."), this);
    m_openAction->setIcon(QIcon(GIMG("open.png")));
    m_openAction->setShortcut(QKeySequence::Open);
    m_openAction->setStatusTip(tr("Open an existing spreadsheet file"));
    connect(m_openAction, SIGNAL(triggered()), this, SLOT(onOpenFile()));

    m_saveAction = new QAction(tr("&Enregistrer"), this);
    m_saveAction->setIcon(QIcon(GIMG("save.png")));
    m_saveAction->setShortcut(QKeySequence::Save);
    m_saveAction->setStatusTip(tr("Enregistrer le tableur sur le disque"));
    connect(m_saveAction, SIGNAL(triggered()), this, SLOT(onSave()));

    m_saveAsAction = new QAction(tr("Enregistrer &sous..."), this);
    m_saveAsAction->setStatusTip(tr("Enregsitrer le tableur dans un nouveau fichier"));
    connect(m_saveAsAction, SIGNAL(triggered()), this, SLOT(onSaveAs()));

    for (int i = 0; i < MaxRecentFiles; ++i) {
        m_recentFileActions[i] = new QAction(this);
        m_recentFileActions[i]->setVisible(false);
        connect(m_recentFileActions[i], SIGNAL(triggered()), this, SLOT(onOpenRecentFile()));
    }

    m_exitAction = new QAction(tr("&Quitter"), this);
    m_exitAction->setShortcut(tr("Ctrl+Q"));
    m_exitAction->setStatusTip(tr("Exit the application"));
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // options
    m_showGridAction = new QAction(tr("&Afficher la grille"), this);
    m_showGridAction->setCheckable(true);
    m_showGridAction->setChecked(m_spreadsheet->showGrid());
    m_showGridAction->setStatusTip(tr("Afficher ou masquer la grille du tableur"));
    connect(m_showGridAction, SIGNAL(toggled(bool)), m_spreadsheet, SLOT(setShowGrid(bool)));

    m_autoRecalcAction = new QAction(tr("&Auto-Recalculer"), this);
    m_autoRecalcAction->setCheckable(true);
    m_autoRecalcAction->setChecked(m_spreadsheet->getAutoRecalculate());
    m_autoRecalcAction->setStatusTip(tr("Activer ou désactiver le recalcul automatique"));
    connect(m_autoRecalcAction, SIGNAL(toggled(bool)), m_spreadsheet, SLOT(setAutoRecalculate(bool)));
}
//===============================================
void GQtSpreadWindow::createMenus() {
    GQTLOG->showMsg(GMSG);
    // fichier
    m_fileMenu = menuBar()->addMenu(tr("&Fichier"));
    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addAction(m_saveAction);
    m_fileMenu->addAction(m_saveAsAction);
    m_separatorAction = m_fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i) {
        m_fileMenu->addAction(m_recentFileActions[i]);
    }
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    // options
    m_optionsMenu = menuBar()->addMenu(tr("&Options"));
    m_optionsMenu->addAction(m_showGridAction);
    m_optionsMenu->addAction(m_autoRecalcAction);
}
//===============================================
bool GQtSpreadWindow::saveFile(const QString& _filename) {
    GQTLOG->showMsg(GMSG);
    if(!m_spreadsheet->saveFile(_filename)) {
        statusBar()->showMessage(tr("Erreur la sauvegarde du tableur a échoué"), 2000);
        GQTLOG->addError(tr("Erreur la sauvegarde du tableur a échoué"));
        return false;
    }
    setCurrentFile(_filename);
    statusBar()->showMessage(tr("Le tableur a été sauvegardé"), 2000);
    return true;
}
//===============================================
bool GQtSpreadWindow::loadFile(const QString& _filename) {
    if (!m_spreadsheet->loadFile(_filename)) {
        statusBar()->showMessage(tr("Erreur le chargement du tableur a échoué"), 2000);
        return false;
    }

    setCurrentFile(_filename);
    statusBar()->showMessage(tr("Le tableur a été chargé"), 2000);
    return true;
}
//===============================================
void GQtSpreadWindow::setCurrentFile(const QString& _filename) {
    GQTLOG->showMsg(GMSG);
    m_currentFile = _filename;
    setWindowModified(false);
    QString lShowName = tr("Untitled");

    if (!m_currentFile.isEmpty()) {
        lShowName = strippedName(m_currentFile);
        m_recentFiles.removeAll(m_currentFile);
        m_recentFiles.prepend(m_currentFile);
        updateRecentFileActions();
    }

    setWindowTitle(tr("%1 | %2[*]").arg(m_params.app_name).arg(lShowName));
}
//===============================================
QString GQtSpreadWindow::strippedName(const QString& _fullname) {
    GQTLOG->showMsg(GMSG);
    return QFileInfo(_fullname).fileName();
}
//===============================================
void GQtSpreadWindow::updateRecentFileActions() {
    GQTLOG->showMsg(GMSG);
    QMutableStringListIterator lFile(m_recentFiles);
    while (lFile.hasNext()) {
        if (!QFile::exists(lFile.next())) {
            lFile.remove();
        }
    }
    for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < m_recentFiles.count()) {
            QString text = tr("&%1 - %2").arg(j + 1).arg(strippedName(m_recentFiles[j]));
            m_recentFileActions[j]->setText(text);
            m_recentFileActions[j]->setData(m_recentFiles[j]);
            m_recentFileActions[j]->setVisible(true);
        }
        else {
            m_recentFileActions[j]->setVisible(false);
        }
    }
    m_separatorAction->setVisible(!m_recentFiles.isEmpty());
}
//===============================================
bool GQtSpreadWindow::okToContinue() {
    if (isWindowModified()) {
        int lOk = QMessageBox::warning(this, m_params.app_name,
                tr("Le document a été modifié.\n"
                "Voulez-vous enregistrer les modifications ?"),
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (lOk == QMessageBox::Yes) {
            return onSave();
        }
        else if (lOk == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}
//===============================================
void GQtSpreadWindow::writeSettings() {
    QSettings lSettings(m_params.organization_name, m_params.app_name);
    lSettings.setValue("geometry", saveGeometry());
    lSettings.setValue("recentFiles", m_recentFiles);
    lSettings.setValue("showGrid", m_showGridAction->isChecked());
    lSettings.setValue("autoRecalc", m_autoRecalcAction->isChecked());
}
//===============================================
void GQtSpreadWindow::readSettings() {
    QSettings lSettings(m_params.organization_name, m_params.app_name);
    restoreGeometry(lSettings.value("geometry").toByteArray());
    m_recentFiles = lSettings.value("recentFiles").toStringList();
    updateRecentFileActions();
    bool lShowGrid = lSettings.value("showGrid", true).toBool();
    m_showGridAction->setChecked(lShowGrid);
    bool lAutoRecalc = lSettings.value("autoRecalc", true).toBool();
    m_autoRecalcAction->setChecked(lAutoRecalc);
}
//===============================================
void GQtSpreadWindow::closeEvent(QCloseEvent *event) {
    if (okToContinue()) {
        writeSettings();
        event->accept();
    }
    else {
        event->ignore();
    }
}
//===============================================
void GQtSpreadWindow::onNewFile() {
    GQTLOG->showMsg(GMSG);
}
//===============================================
void GQtSpreadWindow::onOpenFile() {
    GQTLOG->showMsg(GMSG);
    if (okToContinue()) {
        QString lFilename = QFileDialog::getOpenFileName(this,
                tr("Ouvrir un tableur"), ".",
                tr("Spreadsheet files (*.sp)"));
        if (!lFilename.isEmpty()) {
            loadFile(lFilename);
        }
    }
}
//===============================================
bool GQtSpreadWindow::onSave() {
    GQTLOG->showMsg(GMSG);
    if (m_currentFile.isEmpty()) {
        return onSaveAs();
    }
    else {
        return saveFile(m_currentFile);
    }
    return true;
}
//===============================================
bool GQtSpreadWindow::onSaveAs() {
    GQTLOG->showMsg(GMSG);
    QString lFilename = QFileDialog::getSaveFileName(this,
            tr("Enregistrer le tableur"), ".",
            tr("Spreadsheet files (*.sp)"));
    if (lFilename.isEmpty()) {
        return false;
    }

    return saveFile(lFilename);
}
//===============================================
void GQtSpreadWindow::onOpenRecentFile() {
    if (okToContinue()) {
        QAction* action = qobject_cast<QAction*>(sender());
        if (action)
            loadFile(action->data().toString());
    }
}
//===============================================
