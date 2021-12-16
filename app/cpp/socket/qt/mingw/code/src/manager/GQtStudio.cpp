//===============================================
#include "GQtStudio.h"
#include "GQtXml.h"
#include "GQtResource.h"
#include "GQtLog.h"
//===============================================
GQtStudio::GQtStudio(QWidget* _parent) :
GQtMainWindow(_parent) {
    createDoms();
    createActions();
    setWindowTitle(getTitle());
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
void GQtStudio::createActions() {
    for(int i = 0; i < 3; i++) {
        menuBar()->addMenu(tr("&File"));
    }
}
//===============================================
QString GQtStudio::getTitle() const {
    m_dom->getRoot("rdv").getNode("settings");
    QString lTitle = m_dom->getNode("appname").getNodeValue();
    return lTitle;
}
//===============================================
int GQtStudio::getWidth() const {
    m_dom->getRoot("rdv").getNode("settings");
    QString lWidth = m_dom->getNode("width").getNodeValue();
    return lWidth.toInt();
}
//===============================================
int GQtStudio::getHeight() const {
    m_dom->getRoot("rdv").getNode("settings");
    QString lHeight = m_dom->getNode("height").getNodeValue();
    return lHeight.toInt();
}
//===============================================
