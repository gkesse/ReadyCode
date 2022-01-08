//===============================================
#include "GQtMainWindow.h"
#include "GQtXml.h"
#include "GQtObject.h"
#include "GQtLog.h"
//===============================================
GQtMainWindow::GQtMainWindow(QWidget* _parent) :
QMainWindow(_parent) {
    createDoms();
}
//===============================================
GQtMainWindow::~GQtMainWindow() {

}
//===============================================
void GQtMainWindow::createActions() {
    // menu count
    int lCountMenus = countMenus();
    // menu loop
    for(int i = 0; i < lCountMenus; i++) {
        // menu name
        QString lMenuName = getMenuName(i);
        if(lMenuName == "") continue;
        // menu sep
        bool lMenuSep = getMenuSep(i);
        // menu sep exist
        if(lMenuSep) {
            menuBar()->addSeparator();
        }
        // menu add
        QMenu* lMenu = menuBar()->addMenu(lMenuName);
        // submenu count
        int lCountSubMenus = countSubMenus(i);
        // toolbar on
        bool lMenuToolBarOn = getMenuToolBarOn(i);
        QToolBar* lToolBar = 0;
        // toolbar exist
        if(lMenuToolBarOn) {
            // toolbar add
            lToolBar = addToolBar(lMenuName);
        }
        // submenu loop
        for(int j = 0; j < lCountSubMenus; j++) {
            QString lSubMenuName = getSubMenuName(i, j);
            QString lSubMenuBoxName = getSubMenuBoxName(i, j);
            // submenu name exist
            if(lSubMenuName != "") {
                // submenu action
                QAction* lAction = new QAction(this);
                lAction->setText(lSubMenuName);
                // submenu icon
                QString lSubMenuIcon = getSubMenuIcon(i, j);
                bool lSubMenuCheckBox = getSubMenuCheckBox(i, j);
                // submenu icon exist
                if(lSubMenuIcon != "") {
                    lAction->setIcon(QIcon(GQTRES("studio/img", lSubMenuIcon)));
                }
                // submenu checkbox exist
                else if(lSubMenuCheckBox) {
                    lAction->setCheckable(true);
                }
                // submenu statustip
                QString lSubMenuStatusTip = getSubMenuStatusTip(i, j);
                // submenu statustip exist
                if(lSubMenuStatusTip != "") {
                    lAction->setStatusTip(lSubMenuStatusTip);
                }
                // submenu key
                QString lSubMenuKey = getSubMenuKey(i, j);
                // submenu key exist
                if(lSubMenuKey != "") {
                    // submenu key set
                    lAction->setData(lSubMenuKey);
                    bool lSubMenuCtrlOn = getSubMenuCtrlOn(i, j);
                    // submenu ctrl exist
                    if(lSubMenuCtrlOn) {
                        // submenu ctrl set
                        m_keyAction[lSubMenuKey] = lAction;
                    }
                }
                // submenu shortcut
                QString lSubMenuShortcut = getSubMenuShortcut(i, j);
                // submenu shortcut exist
                if(lSubMenuShortcut != "") {
                    // submenu shortcut set
                    lAction->setShortcut(lSubMenuShortcut);
                }
                // menu action add
                lMenu->addAction(lAction);
                // menu toolbar on exist
                if(lMenuToolBarOn) {
                    // submenu toolbar sep
                    bool lSubMenuToolBarSep = getSubMenuToolBarSep(i, j);
                    // submenu toolbar on
                    bool lSubMenuToolBarOn = getSubMenuToolBarOn(i, j);
                    // submenu toolbar exist
                    if(lSubMenuToolBarSep) {
                        // submenu toolbar separator add
                        lToolBar->addSeparator();
                    }
                    if(lSubMenuToolBarOn) {
                        // submenu toolbar add
                        lToolBar->addAction(lAction);
                    }
                }
                // submenu checkbox exist
                if(lSubMenuCheckBox) {
                    // submenu action connect toggled
                    connect(lAction, SIGNAL(toggled(bool)), this, SLOT(onMenuAction(bool)));
                }
                else {
                    // submenu action connect triggered
                    connect(lAction, SIGNAL(triggered()), this, SLOT(onMenuAction()));
                }
            }
            // menu box name exist
            else if(lSubMenuBoxName != "") {
                // menu box add
                QMenu* lBox = lMenu->addMenu(lSubMenuBoxName);
                // get menu box key
                QString lSubMenuBoxKey = getSubMenuBoxKey(i, j);
                // menu box key exist
                if(lSubMenuBoxKey != "") {
                    // menu box key set
                    m_menuKey[lBox] = lSubMenuBoxKey;
                    connect(lBox, SIGNAL(aboutToShow()), this, SLOT(onMenuBox()));
                    bool lSubMenuBoxCtrlOn = getSubMenuBoxCtrlOn(i, j);
                    // menu box ctrl exist
                    if(lSubMenuBoxCtrlOn) {
                        // menu box ctrl set
                        m_keyAction[lSubMenuBoxKey] = lBox->menuAction();
                    }
                }
                // menu recent files on
                bool lSubMenuBoxRecentFileOn = getSubMenuBoxRecentFileOn(i, j);
                // menu recent files exist
                if(lSubMenuBoxRecentFileOn) {
                    int lSubMenuBoxRecentFileMax = getSubMenuBoxRecentFileMaxValue(i, j);
                    bool lSubMenuBoxRecentFileMaxCtrlOn = getSubMenuBoxRecentFileMaxCtrlOn(i, j);
                    QString lSubMenuBoxRecentFileMaxKey = getSubMenuBoxRecentFileMaxKey(i, j);
                    // menu recent files max ctrl exist
                    if(lSubMenuBoxRecentFileMaxCtrlOn) {
                        m_keyInt[lSubMenuBoxRecentFileMaxKey] = lSubMenuBoxRecentFileMax;
                    }
                    // menu recent files max loop
                    for(int k = 0; k < lSubMenuBoxRecentFileMax; k++) {
                        QAction* lBoxAction = new QAction(this);
                        lBoxAction->setVisible(false);
                        lBox->addAction(lBoxAction);
                        connect(lBoxAction, SIGNAL(triggered()), this, SLOT(onBoxRecentFile()));
                        // menu recent files max ctrl exist
                        if(lSubMenuBoxRecentFileMaxCtrlOn) {
                            m_keyAction[getKeyIndex(lSubMenuBoxKey, k)] = lBoxAction;
                        }
                    }
                }
                // menu box exist
                else {
                    // menu box count
                    int lCountBoxMenus = countBoxMenus(i, j);
                    // radiobutton on
                    bool lRadioButtonOn = getRadioButton(i, j);
                    // menu box key
                    QString lKey = getMenuKey(i, j);
                    // menu box index
                    int lIndex = getMenuIndex(i, j);
                    // menu box index ctrl
                    bool lIndexCtrl = getMenuIndexCtrl(i, j);
                    // menu box index ctrl exist
                    if(lIndexCtrl) {
                        if(lKey != "") {
                            QString lKeyI = QString("%1/index/i").arg(lKey);
                            QString lKeyJ = QString("%1/index/j").arg(lKey);
                            m_keyInt[lKeyI] = i;
                            m_keyInt[lKeyJ] = j;
                        }
                    }
                    // radiobutton exist
                    QActionGroup* lActionGroup = 0;
                    if(lRadioButtonOn) {
                        lActionGroup = new QActionGroup(this);
                        lActionGroup->setExclusive(true);
                    }
                    // menu box loop
                    for(int k = 0; k < lCountBoxMenus; k++) {
                        // menu box name
                        QString lName = getBoxMenuName(i, j, k);
                        // menu box key
                        QString lMenuKey = getBoxMenuKey(i, j, k);
                        QAction* lBoxAction = new QAction(this);
                        lBoxAction->setText(lName);
                        // radiobutton exist
                        if(lRadioButtonOn) {
                            lActionGroup->addAction(lBoxAction);
                            lBoxAction->setCheckable(true);
                            if(lIndex == k) {
                                lBoxAction->setChecked(true);
                            }
                        }
                        // menu box key exist
                        if(lMenuKey != "") {
                            lBoxAction->setData(lMenuKey);
                        }
                        // menu box action add
                        lBox->addAction(lBoxAction);
                        // menu box action connect triggered
                        connect(lBoxAction, SIGNAL(triggered()), this, SLOT(onMenuAction()));
                    }
                }
            }
            // menu separator exist
            else {
                // get menu separator on
                bool lSubMenuSeparatorOn = getSubMenuSeparatorOn(i, j);
                // if menu separator on exist
                if(lSubMenuSeparatorOn) {
                    QAction* lAction = lMenu->addSeparator();
                    bool lSubMenuCtrlOn = getSubMenuCtrlOn(i, j);
                    if(lSubMenuCtrlOn) {
                        QString lSubMenuKey = getSubMenuKey(i, j);
                        m_keyAction[lSubMenuKey] = lAction;
                    }
                }
            }
            // submenu highline end
        } // submenu loop end
    } // menu loop end
}
//===============================================
void GQtMainWindow::createStatusBar() {
    statusBar()->showMessage("Prêt");
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
    setRecentFilesVisible(hasRecentFiles());
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
void GQtMainWindow::updateRecentFiles(const QString& _recentFileMaxKey, const QString& _recentFileKey) {
    QStringList recentFiles = readRecentFiles();
    int lMax = getKeyInt(_recentFileMaxKey);
    int lCount = qMin(lMax, recentFiles.size());
    for(int i = 0; i < lMax; i++) {
        QString lKey = getKeyIndex(_recentFileKey, i);
        QAction* lAction = getKeyAction(lKey);
        if(i < lCount) {
            const QString fileName = strippedName(recentFiles.at(i));
            lAction->setText(tr("&%1 - %2").arg(i + 1).arg(fileName));
            lAction->setData(recentFiles.at(i));
            lAction->setVisible(true);
        }
        else {
            lAction->setVisible(false);
        }
    }
}
//===============================================
QString GQtMainWindow::strippedName(const QString& _fullname) {
    return QFileInfo(_fullname).fileName();
}
//===============================================
int GQtMainWindow::countRecentFiles() const {
    m_domData->queryXPath(QString("/rdv/recentfiles/name"));
    int lData = m_domData->countXPath();
    return lData;
}
//===============================================
bool GQtMainWindow::hasRecentFiles() const {
    bool lData = (countRecentFiles() != 0);
    return lData;
}
//===============================================
QString GQtMainWindow::getRecentFile(int _name) const {
    m_domData->queryXPath(QString("/rdv/recentfiles/name[position()=%1]").arg(_name));
    m_domData->getNodeXPath();
    QString lData = m_domData->getNodeValue();
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
    m_domData->queryXPath(QString("/rdv/recentfiles/name"));
    m_domData->clearNodeXPath();
    m_domData->saveXmlFile();
}
//===============================================
void GQtMainWindow::appendRecentFile(QString _recentFile) {
    m_domData->queryXPath(QString("/rdv/recentfiles"));
    m_domData->getNodeXPath();
    m_domData->getRoot("rdv").getNode("recentfiles");
    GQtXml lNode;
    lNode.createNodeValue("name", _recentFile);
    m_domData->appendNode(lNode);
    m_domData->saveXmlFile();
}
//===============================================
void GQtMainWindow::createDoms() {

}
//===============================================
QString GQtMainWindow::getTitle() const {
    m_dom->queryXPath("/rdv/settings/appname");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getVersion() const {
    m_dom->queryXPath("/rdv/settings/version");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getAbout() const {
    if(getAboutId() != "") {
        return getWordCData(getAboutId());
    }
    else {
        return getAboutText();
    }
    return "";
}
//===============================================
QString GQtMainWindow::getAboutId() const {
    m_dom->queryXPath("/rdv/settings/about/id");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getAboutText() const {
    m_dom->queryXPath("/rdv/settings/about/text");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getLogo() const {
    m_dom->queryXPath("/rdv/settings/logo");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GQtMainWindow::getWidth() const {
    m_dom->queryXPath("/rdv/settings/width");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
int GQtMainWindow::getHeight() const {
    m_dom->queryXPath("/rdv/settings/height");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
QString GQtMainWindow::getWindowFlag() const {
    m_dom->queryXPath("/rdv/settings/windowflag");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getUntitledName() const {
    m_dom->queryXPath("/rdv/settings/untitled/name");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getUntitledExtension() const {
    m_dom->queryXPath("/rdv/settings/untitled/extension");
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GQtMainWindow::countMenus() const {
    m_dom->queryXPath("/rdv/menus/menu");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
int GQtMainWindow::countSubMenus(int _menu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu").arg(_menu + 1));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
int GQtMainWindow::countBoxMenus(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/submenus/submenu").arg(_menu + 1).arg(_submenu + 1));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
bool GQtMainWindow::getRadioButton(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/radiobutton").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
QString GQtMainWindow::getMenuKey(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/key").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GQtMainWindow::getMenuIndex(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/index").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
bool GQtMainWindow::getMenuIndexCtrl(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/indexctrl").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
QString GQtMainWindow::getMenuName(int _menu) const {
    QString lId = getMenuNameId(_menu);
    if(lId != "") {
        return getWord(lId);
    }
    else {
        return getMenuNameText(_menu);
    }
    return "";
}
//===============================================
QString GQtMainWindow::getMenuNameId(int _menu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/id").arg(_menu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getMenuNameText(int _menu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/name").arg(_menu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
bool GQtMainWindow::getMenuSep(int _menu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/menusep").arg(_menu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
QString GQtMainWindow::getBoxMenuName(int _menu, int _submenu, int _box) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/submenus/submenu[position()=%3]/name").arg(_menu + 1).arg(_submenu + 1).arg(_box + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getBoxMenuKey(int _menu, int _submenu, int _box) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/submenus/submenu[position()=%3]/key").arg(_menu + 1).arg(_submenu + 1).arg(_box + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
bool GQtMainWindow::getMenuToolBarOn(int _menu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/toolbar").arg(_menu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
QString GQtMainWindow::getSubMenuName(int _menu, int _submenu) const {
    QString lId = getSubMenuNameId(_menu, _submenu);
    if(lId != "") {
        return getWord(lId);
    }
    else {
        return getSubMenuNameText(_menu, _submenu);
    }
    return "";
}
//===============================================
QString GQtMainWindow::getSubMenuNameId(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/id").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuNameText(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/name").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuBoxName(int _menu, int _submenu) const {
    QString lId = getSubMenuBoxNameId(_menu, _submenu);
    if(lId != "") {
        return getWord(lId);
    }
    else {
        return getSubMenuBoxNameText(_menu, _submenu);
    }
    return "";
}
//===============================================
QString GQtMainWindow::getSubMenuBoxNameId(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/id").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuBoxNameText(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/name").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuBoxKey(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/key").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuBoxRecentFileOn(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/recentfile").arg(_menu + 1).arg(_submenu + 1));
    int lData = m_dom->countXPath();
    return (lData != 0);
}
//===============================================
bool GQtMainWindow::getSubMenuBoxCtrlOn(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/ctrl").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
int GQtMainWindow::getSubMenuBoxRecentFileMaxValue(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/recentfile/max").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData.toInt();
}
//===============================================
bool GQtMainWindow::getSubMenuBoxRecentFileMaxCtrlOn(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/recentfile/ctrl").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
QString GQtMainWindow::getSubMenuBoxRecentFileMaxKey(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/recentfile/key").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuIcon(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/icon").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuCheckBox(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/checkbox").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
QString GQtMainWindow::getSubMenuStatusTip(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/statustip").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuKey(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/key").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuShortcut(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/shortcut").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuToolBarOn(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/toolbar").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
bool GQtMainWindow::getSubMenuToolBarSep(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/toolbarsep").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
bool GQtMainWindow::getSubMenuSeparatorOn(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/separator").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
bool GQtMainWindow::getSubMenuCtrlOn(int _menu, int _submenu) const {
    m_dom->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/ctrl").arg(_menu + 1).arg(_submenu + 1));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
QString GQtMainWindow::getWord(const QString& _id) const {
    QString lData = getWord(_id, getWordLang());
    return lData;
}
//===============================================
QString GQtMainWindow::getWordCData(const QString& _id) const {
    QString lData = getWord(_id, getWordLang());
    return lData;
}
//===============================================
QString GQtMainWindow::getWord(const QString& _id, const QString& _lang) const {
    m_domWord->queryXPath(QString("/rdv/words/word[position()=%1]/%2").arg(_id).arg(_lang));
    m_domWord->getNodeXPath();
    QString lData = m_domWord->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getWordCData(const QString& _id, const QString& _lang) const {
    m_domWord->queryXPath(QString("/rdv/words/word[position()=%1]/%2").arg(_id).arg(_lang));
    m_domWord->getNodeXPath();
    QString lData = m_domWord->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getWordLang() const {
    m_domData->queryXPath(QString("/rdv/lang"));
    m_domData->getNodeXPath();
    QString lData = m_domData->getNodeValue();
    return lData;
}
//===============================================
void GQtMainWindow::setLanguage(const QString& _lang) {
    m_domData->queryXPath(QString("/rdv/lang"));
    m_domData->getNodeXPath();
    m_domData->setNodeValue(_lang);
    m_domData->saveXmlFile();
}
//===============================================
void GQtMainWindow::setLanguageIndex(const QString& _key, const QString& _languageKey) {
    // get index coords
    QString lKeyI = QString("%1/index/i").arg(_languageKey);
    QString lKeyJ = QString("%1/index/j").arg(_languageKey);
    int i = m_keyInt[lKeyI];
    int j = m_keyInt[lKeyJ];
    // get index position
    int lIndex = 0;
    int lCount = countBoxMenus(i, j);
    for(int k = 0; k < lCount; k++) {
        QString lKeyMenu = getBoxMenuKey(i, j, k);
        if(lKeyMenu == _key) {
            lIndex = k;
            break;
        }
    }
    // set index
    setLanguageIndex(i, j, lIndex);
}
//===============================================
void GQtMainWindow::setLanguageIndex(int _menu, int _submenu, int _index) {
    m_domData->queryXPath(QString("/rdv/menus/menu[position()=%1]/submenus/submenu[position()=%2]/menu/index").arg(_menu).arg(_submenu));
    m_domData->getNodeXPath();
    m_domData->setNodeValue(QString("%1").arg(_index));
    m_domData->saveXmlFile();
}
//===============================================
void GQtMainWindow::writeGeometry(const QByteArray& _geometry) {
    m_domData->queryXPath(QString("/rdv/geometry"));
    m_domData->getNodeXPath();
    m_domData->setNodeCData(_geometry.toBase64());
    m_domData->saveXmlFile();
}
//===============================================
QByteArray GQtMainWindow::getGeometry() const {
    m_domData->queryXPath(QString("/rdv/geometry"));
    m_domData->getNodeXPath();
    QString lData = m_domData->getNodeCData();
    QByteArray lData64;
    lData64 += lData;
    QByteArray lDataBA = QByteArray::fromBase64(lData64);
    return lDataBA;
}
//===============================================
bool GQtMainWindow::getDebug() const {
    m_dom->queryXPath(QString("/rdv/settings/debug"));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
void GQtMainWindow::showDebug(const QString& _debug) {
    if(getDebug()) {
        qDebug() << "----->";
        qDebug() << _debug;
    }
}
//===============================================
QAction* GQtMainWindow::getKeyAction(const QString& _key) const {
    QAction* lAction = m_keyAction.value(_key, 0);
    if(lAction == 0) {
        GQTLOG->addError(QString("Erreur la methode (getKeyAction) a echoue\n"
                "sur la cle (%1).").arg(_key));
    }
    return lAction;
}
//===============================================
int GQtMainWindow::getKeyInt(const QString& _key) const {
    int lInt = m_keyInt.value(_key, std::numeric_limits<int>::max());
    if(lInt == std::numeric_limits<qint64>::max()) {
        GQTLOG->addError(QString("Erreur la methode (getKeyInt) a echoue\n"
                "sur la cle (%1).").arg(_key));
    }
    return lInt;
}
//===============================================
QString GQtMainWindow::getKeyIndex(const QString& _key, int _index) const {
    QString lKey = QString("%1/%2").
            arg(_key).
            arg(_index);
    return lKey;
}
//===============================================
void GQtMainWindow::setRecentFilesVisible(bool _visible, const QString& _recentFileKey, const QString& _separatorKey) {
    QAction* lRecentFile = getKeyAction(_recentFileKey);
    QAction* lSeparator = getKeyAction(_separatorKey);
    lRecentFile->setVisible(_visible);
    lSeparator->setVisible(_visible);
}
//===============================================
void GQtMainWindow::onMenuAction() {}
void GQtMainWindow::onMenuAction(bool _checked) {}
void GQtMainWindow::onMenuBox() {}
void GQtMainWindow::onBoxRecentFile() {}
//===============================================
