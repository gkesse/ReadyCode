//===============================================
#include "GQtStudio.h"
#include "GQtSdi.h"
#include "GQtMdi.h"
#include "GQtXml.h"
#include "GQtObject.h"
#include "GQtLog.h"
//===============================================
GQtStudio::GQtStudio(QWidget* _parent) :
GQtMainWindow(_parent) {
    createDoms();
    createActions();
    createWindows();
    setWindowTitle(getTitle());
    setWindowIcon(QIcon(GQTRES("studio/img", getLogo())));
    resize(getWidth(), getHeight());
    GQTLOG->showErrorQt(this);
}
//===============================================
GQtStudio::~GQtStudio() {

}
//===============================================
void GQtStudio::createDoms() {
    m_dom.reset(new GQtXml);
    m_dom->loadXmlFile(GQTRES("studio/xml", "studio.xml"));
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
    else if(lKey == "qt/mainwindow/mdi") {
        GQtMdi* lMdiWindow = new GQtMdi;
        lMdiWindow->setWindowFlag(this);
        lMdiWindow->show();
        lMdiWindow->activateWindow();
    }
}
//===============================================
