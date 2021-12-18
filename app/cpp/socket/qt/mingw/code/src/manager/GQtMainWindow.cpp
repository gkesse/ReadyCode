//===============================================
#include "GQtMainWindow.h"
#include "GQtXml.h"
#include "GQtResource.h"
#include "GQtLog.h"
//===============================================
GQtMainWindow::GQtMainWindow(QWidget* _parent) :
QMainWindow(_parent) {

}
//===============================================
GQtMainWindow::~GQtMainWindow() {

}
//===============================================
void GQtMainWindow::createActions() {
    int lCountMenus = countMenus();
    for(int i = 0; i < lCountMenus; i++) {
        QString lMenuName = getMenuName(i);
        if(lMenuName == "") continue;
        QMenu* lMenu = menuBar()->addMenu(lMenuName);
        int lCountSubMenus = countSubMenus(i);
        bool lMenuToolBarOn = getMenuToolBarOn(i);
        QToolBar* lToolBar = 0;
        if(lMenuToolBarOn) {
            lToolBar = addToolBar(lMenuName);
        }
        for(int j = 0; j < lCountSubMenus; j++) {
            QString lSubMenuName = getSubMenuName(i, j);
            QString lSubMenuBox = getSubMenuBox(i, j);
            if(lSubMenuName != "") {
                QAction* lAction = new QAction(this);
                lAction->setText(lSubMenuName);
                QString lSubMenuIcon = getSubMenuIcon(i, j);
                if(lSubMenuIcon != "") {
                    lAction->setIcon(QIcon(GQTIMG(lSubMenuIcon)));
                }
                QString lSubMenuStatusTip = getSubMenuStatusTip(i, j);
                if(lSubMenuStatusTip != "") {
                    lAction->setStatusTip(lSubMenuStatusTip);
                }
                QString lSubMenuKey = getSubMenuKey(i, j);
                if(lSubMenuKey != "") {
                    lAction->setData(lSubMenuKey);
                }
                QString lSubMenuShortcut = getSubMenuShortcut(i, j);
                if(lSubMenuShortcut != "") {
                    lAction->setShortcut(lSubMenuShortcut);
                }
                lMenu->addAction(lAction);
                if(lMenuToolBarOn) {
                    bool lSubMenuToolBarOn = getSubMenuToolBarOn(i, j);
                    if(lSubMenuToolBarOn) {
                        lToolBar->addAction(lAction);
                    }
                }
                connect(lAction, SIGNAL(triggered()), this, SLOT(onMenuAction()));
            }
            else if(lSubMenuBox != "") {
                QMenu* lBox = lMenu->addMenu(lSubMenuBox);
                int lCountBoxMenus = countBoxMenus(i, j);
                for(int k = 0; k < lCountBoxMenus; k++) {
                    QString lName = getBoxMenuName(i, j, k);
                    QAction* lBoxAction = new QAction(this);
                    lBoxAction->setText(lName);
                    lBox->addAction(lBoxAction);
                }
            }
            else {
                bool lSubMenuSeparatorOn = getSubMenuSeparatorOn(i, j);
                if(lSubMenuSeparatorOn) {
                    lMenu->addSeparator();
                }
            }
        }
    }
}
//===============================================
void GQtMainWindow::setWindowFlag(QWidget* _parent) {
    QString lWindowFlag = getWindowFlag();
    if(lWindowFlag == "QT_TOOL") {
        setParent(_parent);
        setWindowFlags(Qt::Tool);
    }
}
//===============================================
void GQtMainWindow::prependToRecentFiles(const QString& _filename) {
    const QStringList oldRecentFiles = readRecentFiles();
    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(_filename);
    recentFiles.prepend(_filename);
    if (oldRecentFiles != recentFiles) {
        writeRecentFiles(recentFiles);
    }
    setRecentFilesVisible(!recentFiles.isEmpty());
}
//===============================================
void GQtMainWindow::setRecentFilesVisible(bool _visible) {

}
//===============================================
QStringList GQtMainWindow::readRecentFiles() {
    QStringList lRecentFiles;
    int lCountRecentFiles = countRecentFiles();
    for(int i = 0; i < lCountRecentFiles; i++) {
        QString lRecentFile = getRecentFile(i);
        lRecentFiles.push_back(lRecentFile);
    }
    return lRecentFiles;
}
//===============================================
int GQtMainWindow::countRecentFiles() const {
    m_domData->getRoot("rdv").getNode("recentfiles");
    int lCount = m_domData->getNodeCount("name");
    return lCount;
}
//===============================================
QString GQtMainWindow::getRecentFile(int _name) const {
    m_domData->getRoot("rdv").getNode("recentfiles");
    QString lData = m_domData->getNodeItem("name", _name).getNodeValueOrEmpty();
    return lData;
}
//===============================================
void GQtMainWindow::writeRecentFiles(QStringList _recentFiles) {
    clearRecentFiles();
    for(int i = 0; i < _recentFiles.size(); i++) {
        QString lRecentFile = _recentFiles.at(i);
        appendRecentFile(lRecentFile);
    }
}
//===============================================
void GQtMainWindow::clearRecentFiles() {
    m_domData->getRoot("rdv").getNode("recentfiles");
    m_domData->clearNode("name");
    m_domData->saveFile();
}
//===============================================
void GQtMainWindow::appendRecentFile(QString _recentFile) {
    m_domData->getRoot("rdv").getNode("recentfiles");
    GQtXml lNode(m_domData.get());
    lNode.createNodeText("name", _recentFile);
    m_domData->appendNode(lNode);
    m_domData->saveFile();
}
//===============================================
int GQtMainWindow::countMenus() const {
    m_dom->getRoot("rdv").getNode("menus");
    int lCount = m_dom->getNodeCount("menu");
    return lCount;
}
//===============================================
int GQtMainWindow::countSubMenus(int _menu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    int lCount = m_dom->getNodeCount("submenu");
    return lCount;
}
//===============================================
int GQtMainWindow::countBoxMenus(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNode("menu").getNode("submenus");
    int lCount = m_dom->getNodeCount("submenu");
    return lCount;
}
//===============================================
QString GQtMainWindow::getMenuName(int _menu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu);
    QString lData = m_dom->getNodeOrEmpty("name").getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getBoxMenuName(int _menu, int _submenu, int _box) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNode("menu");
    m_dom->getNode("submenus").getNodeItem("submenu", _box);
    QString lData = m_dom->getNodeOrEmpty("name").getNodeValueOrEmpty();
    return lData;
}
//===============================================
bool GQtMainWindow::getMenuToolBarOn(int _index) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _index);
    bool lData = (m_dom->getNodeOrEmpty("toolbar").getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuName(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu);
    QString lData = m_dom->getNodeOrEmpty("name").getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuBox(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("menu");
    QString lData = m_dom->getNodeOrEmpty("name").getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuIcon(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu);
    QString lData = m_dom->getNodeOrEmpty("icon").getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuStatusTip(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu);
    QString lData = m_dom->getNodeOrEmpty("statustip").getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuKey(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu);
    QString lData = m_dom->getNodeOrEmpty("key").getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuShortcut(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu);
    QString lData = m_dom->getNodeOrEmpty("shortcut").getNodeValueOrEmpty();
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuToolBarOn(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu);
    bool lData = (m_dom->getNodeOrEmpty("toolbar").getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuSeparatorOn(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu);
    bool lData = (m_dom->getNodeOrEmpty("separator").getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
QString GQtMainWindow::getTitle() const {
    m_dom->getRoot("rdv").getNode("settings");
    QString lData = m_dom->getNode("appname").getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getLogo() const {
    m_dom->getRoot("rdv").getNode("settings");
    QString lData = m_dom->getNode("logo").getNodeValue();
    return lData;
}
//===============================================
int GQtMainWindow::getWidth() const {
    m_dom->getRoot("rdv").getNode("settings");
    QString lData = m_dom->getNode("width").getNodeValue();
    return lData.toInt();
}
//===============================================
int GQtMainWindow::getHeight() const {
    m_dom->getRoot("rdv").getNode("settings");
    QString lData = m_dom->getNode("height").getNodeValue();
    return lData.toInt();
}
//===============================================
QString GQtMainWindow::getWindowFlag() const {
    m_dom->getRoot("rdv").getNode("settings");
    QString lData = m_dom->getNodeOrEmpty("windowflag").getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getUntitledName() const {
    m_dom->getRoot("rdv").getNode("untitled");
    QString lData = m_dom->getNodeOrEmpty("name").getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getUntitledExtension() const {
    m_dom->getRoot("rdv").getNode("untitled");
    QString lData = m_dom->getNodeOrEmpty("extension").getNodeValueOrEmpty();
    return lData;
}
//===============================================
void GQtMainWindow::onMenuAction() {}
//===============================================
