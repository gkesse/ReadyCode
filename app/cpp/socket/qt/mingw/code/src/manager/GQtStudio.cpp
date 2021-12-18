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
    m_sdiWindow = new GQtSdi;
    m_sdiWindow->setWindowFlag(this);
}
//===============================================
void GQtStudio::onMenuAction() {
    QAction* lAction = qobject_cast<QAction*>(sender());
    QString lKey = lAction->data().toString();
    qDebug() << lKey;

    if(lKey == "qt/mainwindow/sdi") {
        m_sdiWindow->show();
        m_sdiWindow->activateWindow();
    }
}
//===============================================
