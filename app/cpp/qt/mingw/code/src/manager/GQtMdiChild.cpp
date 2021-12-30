//===============================================
#include "GQtMdiChild.h"
#include "GQtLog.h"
//===============================================
int GQtMdiChild::m_sequenceNumber = 1;
//===============================================
GQtMdiChild::GQtMdiChild(QWidget* _parent) :
GQtTextEdit(_parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
}
//===============================================
GQtMdiChild::~GQtMdiChild() {

}
//===============================================
void GQtMdiChild::newFile(const QString& _title) {
    isUntitled = true;
    curFile = tr("document%1.txt").arg(m_sequenceNumber++);
    QString lTitle = curFile;
    if(_title != "") {
        lTitle = QString("%1 - %2").arg(_title).arg(lTitle);
    }
    setWindowTitle(QString("%1[*]").arg(lTitle));
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
}
//===============================================
bool GQtMdiChild::loadFile(const QString& _filename) {
    QFile file(_filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        GQTLOG->addError(QString("Erreur la methode (loadFile) a echoue "
                "sur le fichier (%1).\n").arg(_filename));
        return false;
    }

    QTextStream in(&file);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QGuiApplication::restoreOverrideCursor();

    setCurrentFile(_filename);
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
    return true;
}
//===============================================
bool GQtMdiChild::save() {
    if (isUntitled) {
        return saveAs();
    }
    else {
        return saveFile(curFile);
    }
}
//===============================================
bool GQtMdiChild::saveAs() {
    QString lTitle = "Enregistrer Sous";
    QString lFilename = QFileDialog::getSaveFileName(this, lTitle, curFile);
    if (lFilename.isEmpty()) {
        return false;
    }
    return saveFile(lFilename);
}
//===============================================
bool GQtMdiChild::saveFile(const QString& _filename) {
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(_filename);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << toPlainText();
        if (!file.commit()) {
            GQTLOG->addError(QString("Erreur la methode (saveFile) a echoue "
                    "sur le fichier (%1) (1).\n").arg(_filename));
            return false;
        }
    }
    else {
        GQTLOG->addError(QString("Erreur la methode (saveFile) a echoue "
                "sur le fichier (%1) (2).\n").arg(_filename));
        return false;
    }
    QGuiApplication::restoreOverrideCursor();

    setCurrentFile(_filename);
    return true;
}
//===============================================
QString GQtMdiChild::userFriendlyCurrentFile() {
    return strippedName(curFile);
}
//===============================================
QString GQtMdiChild::currentFile() {
    return curFile;
}
//===============================================
void GQtMdiChild::closeEvent(QCloseEvent *event) {
    if (maybeSave()) {
        event->accept();
    }
    else {
        event->ignore();
    }
}
//===============================================
void GQtMdiChild::documentWasModified() {
    setWindowModified(document()->isModified());
}
//===============================================
bool GQtMdiChild::maybeSave() {
    if (!document()->isModified()) {
        return true;
    }
    QString lTitle = "ReadyMDI";
    QString lMessage = QString(""
            "(%1) a été modifié.\n"
            "Voulez-vous enregistrer vos modifications ?"
            "").arg(userFriendlyCurrentFile());
    int lAnswer = QMessageBox::warning(this, lTitle, lMessage, QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if(lAnswer == QMessageBox::Save) {
        return save();
    }
    else if(lAnswer == QMessageBox::Cancel) {
        return false;
    }
    return true;
}
//===============================================
void GQtMdiChild::setCurrentFile(const QString& _filename) {
    curFile = QFileInfo(_filename).canonicalFilePath();
    isUntitled = false;
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}
//===============================================
QString GQtMdiChild::strippedName(const QString& _fullname) {
    return QFileInfo(_fullname).fileName();
}
//===============================================
