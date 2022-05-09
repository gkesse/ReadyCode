//===============================================
#include "GQtSpreadWindow.h"
#include "GQtFindDialog.h"
#include "GQtCellLocation.h"
#include "GQtSortDialog.h"
#include "GQtXml.h"
#include "GQtLog.h"
#include "GQtSpreadSheet.h"
//===============================================
GQtSpreadWindow::GQtSpreadWindow(QWidget* _parent) :
GQtMainWindow(_parent) {
    createDoms();
    createActions();
    createCentralWidget();
    createStatusBar();
    createContextMenu();
    setRecentFilesVisible(hasRecentFiles());
    readSettings();
    setCurrentFile("");

    setWindowIcon(QIcon(GQTRES("studio/img", getLogo())));
    resize(getWidth(), getHeight());
    setUnifiedTitleAndToolBarOnMac(true);

    findDialog = 0;

    GQTLOG->showErrorQt(this);
}
//===============================================
GQtSpreadWindow::~GQtSpreadWindow() {

}
//===============================================
void GQtSpreadWindow::createDoms() {
    m_dom.reset(new GQtXml);
    m_dom->loadXmlFile(GQTRES("studio/xml", "spreadsheet.xml"));
    m_domData.reset(new GQtXml);
    m_domData->loadXmlFile(GQTRES("studio/xml", "spreadsheet_data.xml"));
    m_domWord.reset(new GQtXml);
    m_domWord->loadXmlFile(GQTRES("studio/xml", "spreadsheet_words.xml"));
}
//===============================================
void GQtSpreadWindow::createCentralWidget() {
    spreadsheet = new GQtSpreadSheet;
    setCentralWidget(spreadsheet);
}
//===============================================
void GQtSpreadWindow::createStatusBar() {
    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

    connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(updateStatusBar()));
    connect(spreadsheet, SIGNAL(modified()), this, SLOT(spreadsheetModified()));

    updateStatusBar();
}
//===============================================
void GQtSpreadWindow::updateStatusBar(int currentRow, int currentColumn, int previousRow, int previousColumn) {
    locationLabel->setText(spreadsheet->currentLocation());
    formulaLabel->setText(spreadsheet->currentFormula());
}
//===============================================
void GQtSpreadWindow::spreadsheetModified() {
    setWindowModified(true);
    updateStatusBar();
}
//===============================================
void GQtSpreadWindow::createContextMenu() {
    QAction* cutAction = getKeyAction("edit/cut");
    QAction* copyAction = getKeyAction("edit/copy");
    QAction* pasteAction = getKeyAction("edit/paste");
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}
//===============================================
bool GQtSpreadWindow::getShowGrid() const {
    m_domData->getRoot("rdv").getNode("showgrid");
    bool lData = (m_domData->getNodeValue() == "1");
    return lData;
}
//===============================================
bool GQtSpreadWindow::getAutoRecalculate() const {
    m_domData->getRoot("rdv").getNode("autorecalculate");
    bool lData = (m_domData->getNodeValue() == "1");
    return lData;
}
//===============================================
void GQtSpreadWindow::setShowGrid(bool _showGrig) {
    m_domData->getRoot("rdv").getNode("showgrid");
    QString lData = QString("%1").arg(_showGrig);
    m_domData->setNodeValue(lData);
    m_domData->saveXmlFile();
}
//===============================================
void GQtSpreadWindow::setAutoRecalculate(bool _autoRecalculate) {
    m_domData->getRoot("rdv").getNode("autorecalculate");
    QString lData = QString("%1").arg(_autoRecalculate);
    m_domData->setNodeValue(lData);
    m_domData->saveXmlFile();
}
//===============================================
void GQtSpreadWindow::onMenuAction(bool _checked) {
    QAction* lAction = qobject_cast<QAction*>(sender());
    QString lKey = lAction->data().toString();
    qDebug() << lKey;

    // file
    if(lKey == "file/new") {
        if (okToContinue()) {
            spreadsheet->clear();
            setCurrentFile("");
        }
    }
    else if(lKey == "file/open") {
        QString lTitle = "Ouvrir un tableur";
        QString lFilter = "Fichiers tableur (*.sp)";
        if (okToContinue()) {
            QString lFilename = QFileDialog::getOpenFileName(this, lTitle, ".", lFilter);
            if (!lFilename.isEmpty()) {
                loadFile(lFilename);
            }
        }
    }
    else if(lKey == "file/save") {
        save();
    }
    else if(lKey == "file/save/as") {
        saveAs();
    }
    else if(lKey == "file/exit") {
        qApp->quit();
    }
    // edit
    else if(lKey == "edit/cut") {
        spreadsheet->cut();
    }
    else if(lKey == "edit/copy") {
        spreadsheet->copy();
    }
    else if(lKey == "edit/paste") {
        spreadsheet->paste();
    }
    else if(lKey == "edit/delete") {
        spreadsheet->del();
    }
    else if(lKey == "edit/select/row") {
        spreadsheet->selectCurrentRow();
    }
    else if(lKey == "edit/select/column") {
        spreadsheet->selectCurrentColumn();
    }
    else if(lKey == "edit/select/all") {
        spreadsheet->selectAll();
    }
    else if(lKey == "edit/find") {
        if (!findDialog) {
            findDialog = new GQtFindDialog(this);
            connect(findDialog, SIGNAL(findNext(const QString&, Qt::CaseSensitivity)),
                    spreadsheet, SLOT(findNext(const QString&, Qt::CaseSensitivity)));
            connect(findDialog, SIGNAL(findPrevious(const QString&, Qt::CaseSensitivity)),
                    spreadsheet, SLOT(findPrevious(const QString&, Qt::CaseSensitivity)));
        }

        findDialog->show();
        findDialog->raise();
        findDialog->activateWindow();
    }
    else if(lKey == "edit/gotocell") {
        GQtCellLocation dialog(this);
        if (dialog.exec()) {
            QString str = dialog.getText().toUpper();
            spreadsheet->setCurrentCell(str.mid(1).toInt() - 1, str[0].unicode() - 'A');
        }
    }
    // tools
    else if(lKey == "tools/recalculate") {
        spreadsheet->recalculate();
    }
    else if(lKey == "tools/sort") {
        GQtSortDialog dialog(this);
        QTableWidgetSelectionRange range = spreadsheet->selectedRange();
        dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());

        if (dialog.exec()) {
            GQtSpreadSheetCompare compare;
            compare.keys[0] = dialog.currentIndexColumnCombo(1);
            compare.keys[1] = dialog.currentIndexColumnCombo(2) - 1;
            compare.keys[2] = dialog.currentIndexColumnCombo(3) - 1;
            compare.ascending[0] = (dialog.currentIndexOrderCombo(1) == 0);
            compare.ascending[1] = (dialog.currentIndexOrderCombo(2) == 0);
            compare.ascending[2] = (dialog.currentIndexOrderCombo(3) == 0);
            spreadsheet->sort(compare);
        }
    }
    // options
    else if(lKey == "options/show/grid") {
        spreadsheet->setShowGrid(_checked);
    }
    else if(lKey == "options/auto/recalculate") {
        spreadsheet->setAutoRecalculate(_checked);
    }
    // help
    else if(lKey == "help/about/app") {
        QString lTitle = getTitle();
        QString lVersion = getVersion();
        QString lMessage = getAbout().arg(lTitle).arg(lVersion);
        QMessageBox::about(this, lTitle, lMessage);
    }
    else if(lKey == "help/about/qt") {
        qApp->aboutQt();
    }
    if(lKey == "help/language/fr") {
        setLanguageIndex(lKey);
        setLanguage("fr");
    }
    else if(lKey == "help/language/en") {
        setLanguageIndex(lKey);
        setLanguage("en");
    }}
//===============================================
void GQtSpreadWindow::onMenuBox() {
    QMenu* lMenu = qobject_cast<QMenu*>(sender());
    QString lKey = m_menuKey[lMenu];
    qDebug() << lKey;

    if(lKey == "file/recent") {
        updateRecentFiles();
    }
}
//===============================================
void GQtSpreadWindow::onBoxRecentFile() {
    if (okToContinue()) {
        QAction* lAction = qobject_cast<QAction*>(sender());
        if (lAction) {
            QString lFilename = lAction->data().toString();
            qDebug() << lFilename;
            loadFile(lFilename);
        }
    }
}
//===============================================
bool GQtSpreadWindow::loadFile(const QString& _filename) {
    if (!spreadsheet->readFile(_filename)) {
        statusBar()->showMessage(tr("Erreur le chargement du tableur a échoué"), 2000);
        return false;
    }

    setCurrentFile(_filename);
    statusBar()->showMessage(tr("Le tableur a été chargé"), 2000);
    return true;
}
//===============================================
void GQtSpreadWindow::setCurrentFile(const QString& _filename) {
    curFile = _filename;
    setWindowModified(false);

    QString lTitle = getTitle();
    QString shownName = tr("Untitled");
    if (!curFile.isEmpty()) {
        shownName = strippedName(curFile);
        prependToRecentFiles(curFile);
    }

    setWindowTitle(tr("%1 - %2[*]").arg(lTitle).arg(shownName));
}
//===============================================
QString GQtSpreadWindow::strippedName(const QString& _fullname) {
    return QFileInfo(_fullname).fileName();
}
//===============================================
bool GQtSpreadWindow::okToContinue() {
    if (isWindowModified()) {
        QString lTitle = getTitle();
        QString lMessage = QString(""
                "Le document a été modifié.\n"
                "Voulez-vous enregistrer vos modifications?"
                "");
        int lAnswer = QMessageBox::warning(this, lTitle, lMessage,
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (lAnswer == QMessageBox::Yes) {
            return save();
        }
        else if (lAnswer == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}
//===============================================
bool GQtSpreadWindow::save() {
    if (curFile.isEmpty()) {
        return saveAs();
    }
    else {
        return saveFile(curFile);
    }
}
//===============================================
bool GQtSpreadWindow::saveAs() {
    QString lTitle = "Enregistrer sous";
    QString lFilter = "Fichiers tableur (*.sp)";
    QString lFilename = QFileDialog::getSaveFileName(this, lTitle, ".", lFilter);
    if (lFilename.isEmpty()) {
        return false;
    }
    return saveFile(lFilename);
}
//===============================================
bool GQtSpreadWindow::saveFile(const QString& _filename) {
    QString lMsgCancel = "Sauvegarde annulée";
    QString lMsgSave = "Fichier enregistré";
    if (!spreadsheet->writeFile(_filename)) {
        statusBar()->showMessage(lMsgCancel, 2000);
        return false;
    }

    setCurrentFile(_filename);
    statusBar()->showMessage(lMsgSave, 2000);
    return true;
}
//===============================================
void GQtSpreadWindow::writeSettings() {
    QAction* lShowGridAction = getKeyAction("options/show/grid");
    QAction* lAutoRecalculateAction = getKeyAction("options/auto/recalculate");
    writeGeometry(saveGeometry());
    setShowGrid(lShowGridAction->isChecked());
    setAutoRecalculate(lAutoRecalculateAction->isChecked());
}
//===============================================
void GQtSpreadWindow::readSettings() {
    QAction* lShowGridAction = getKeyAction("options/show/grid");
    QAction* lAutoRecalculateAction = getKeyAction("options/auto/recalculate");
    restoreGeometry(getGeometry());
    lShowGridAction->setChecked(getShowGrid());
    lAutoRecalculateAction->setChecked(getAutoRecalculate());
    spreadsheet->setShowGrid(getShowGrid());
    spreadsheet->setAutoRecalculate(getAutoRecalculate());
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
