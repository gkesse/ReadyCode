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
    m_settingsDom.reset(new GQtXml);
    m_settingsDom->openFileRD(GQTXML("settings.xml"));
}
//===============================================
void GQtStudio::createActions() {
    for(int i = 0; i < 3; i++) {
        menuBar()->addMenu(tr("&File"));
    }
}
//===============================================
QString GQtStudio::getTitle() const {
    m_settingsDom->getRoot("rdv").getNode("settings");
    QString lTitle = m_settingsDom->getNode("appname").getNodeValue();
    return lTitle;
}
//===============================================
int GQtStudio::getWidth() const {
    m_settingsDom->getRoot("rdv").getNode("settings");
    QString lWidth = m_settingsDom->getNode("width").getNodeValue();
    return lWidth.toInt();
}
//===============================================
int GQtStudio::getHeight() const {
    m_settingsDom->getRoot("rdv").getNode("settings");
    QString lHeight = m_settingsDom->getNode("height").getNodeValue();
    return lHeight.toInt();
}
//===============================================
