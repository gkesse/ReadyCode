//===============================================
#include "GQtStudio.h"
#include "GQtSdi.h"
#include "GQtXml.h"
#include "GQtResource.h"
#include "GQtLog.h"
//===============================================
GQtStudio::GQtStudio(QWidget* _parent) :
GQtMainWindow(_parent) {
    createDoms();
    createActions();
    createWindows();
    setWindowTitle(getTitle());
    setWindowIcon(QIcon(GQTIMG(getLogo())));
    resize(getWidth(), getHeight());
    GQTLOG->showErrorQt(this);
}
//===============================================
GQtStudio::~GQtStudio() {

}
//===============================================
void GQtStudio::createDoms() {
    m_dom.reset(new GQtXml);
    m_dom->openFileRD(GQTXML("app.xml"));
}
//===============================================
void GQtStudio::createWindows() {

}
//===============================================
void GQtStudio::onMenuAction() {
    QAction* lAction = qobject_cast<QAction*>(sender());
    QString lKey = lAction->data().toString();
    qDebug() << lKey;

    if(lKey == "qt/mainwindow/sdi") {
        GQtSdi* lSdiWindow = new GQtSdi;
        lSdiWindow->setWindowFlag(this);
        lSdiWindow->setPosition(this);
        lSdiWindow->show();
        lSdiWindow->activateWindow();
    }
}
//===============================================
