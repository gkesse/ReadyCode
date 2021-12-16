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
    int lCountMenus = countMenus();
    for(int i = 0; i < lCountMenus; i++) {
        QString lMenuName = getMenuName(i);
        QMenu* lMenu = menuBar()->addMenu(lMenuName);
        int lCountSubMenus = countSubMenus(i);
        for(int j = 0; j < lCountSubMenus; j++) {
            QString lSubMenuName = getSubMenuName(i, j);
            QAction* lAction = new QAction(this);
            lAction->setText(lSubMenuName);
            lMenu->addAction(lAction);
        }
    }
}
//===============================================
int GQtStudio::countMenus() const {
    m_dom->getRoot("rdv").getNode("menus");
    int lCount = m_dom->getNodeCount("menu");
    return lCount;
}
//===============================================
int GQtStudio::countSubMenus(int _menu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    int lCount = m_dom->getNodeCount("submenu");
    return lCount;
}
//===============================================
QString GQtStudio::getMenuName(int _index) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _index);
    QString lMenuName = m_dom->getNode("name").getNodeValue();
    return lMenuName;
}
//===============================================
QString GQtStudio::getSubMenuName(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu);
    QString lSubMenuName = m_dom->getNode("name").getNodeValue();
    return lSubMenuName;
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
