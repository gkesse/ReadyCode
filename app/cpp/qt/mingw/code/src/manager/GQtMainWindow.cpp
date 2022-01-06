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
void GQtMainWindow::createDoms() {

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
                    m_dom->getRoot("rdv").getNode("menus");
                    m_dom->getNodeItem("menu", i).getNode("submenus");
                    m_dom->getNodeItem("submenu", j).getNode("menu");
                    m_dom->getNodeOrEmpty("radiobutton");
                    bool lRadioButtonOn = (m_dom->getNodeValueOrEmpty() == "1");
                    // menu box key
                    m_dom->getRoot("rdv").getNode("menus");
                    m_dom->getNodeItem("menu", i).getNode("submenus");
                    m_dom->getNodeItem("submenu", j).getNode("menu");
                    m_dom->getNodeOrEmpty("key");
                    QString lKey = m_dom->getNodeValueOrEmpty();
                    // menu box index
                    m_dom->getRoot("rdv").getNode("menus");
                    m_dom->getNodeItem("menu", i).getNode("submenus");
                    m_dom->getNodeItem("submenu", j).getNode("menu");
                    m_dom->getNodeOrEmpty("index");
                    int lIndex = m_dom->getNodeValueOrEmpty().toInt();
                    // menu box index ctrl
                    m_dom->getRoot("rdv").getNode("menus");
                    m_dom->getNodeItem("menu", i).getNode("submenus");
                    m_dom->getNodeItem("submenu", j).getNode("menu");
                    m_dom->getNodeOrEmpty("indexctrl");
                    bool lIndexCtrl = (m_dom->getNodeValueOrEmpty() == "1");
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
    m_domData->getRoot("rdv").getNode("recentfiles");
    int lData = m_domData->countNode("name");
    return lData;
}
//===============================================
bool GQtMainWindow::hasRecentFiles() const {
    bool lData = (countRecentFiles() != 0);
    return lData;
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
    m_domData->saveXmlFile();
}
//===============================================
void GQtMainWindow::appendRecentFile(QString _recentFile) {
    m_domData->getRoot("rdv").getNode("recentfiles");
    GQtXml lNode(m_domData.get());
    lNode.createNodeText("name", _recentFile);
    m_domData->appendNode(lNode);
    m_domData->saveXmlFile();
}
//===============================================
int GQtMainWindow::countMenus() const {
    m_dom->getRoot("rdv").getNode("menus");
    int lData = m_dom->countNode("menu");
    return lData;
}
//===============================================
int GQtMainWindow::countSubMenus(int _menu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    int lData = m_dom->countNode("submenu");
    return lData;
}
//===============================================
int GQtMainWindow::countBoxMenus(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNode("menu").getNode("submenus");
    int lData = m_dom->countNode("submenu");
    return lData;
}
//===============================================
QString GQtMainWindow::getMenuName(int _menu) const {
    QString lData;
    // get id
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNodeOrEmpty("id");
    QString lId = m_dom->getNodeValueOrEmpty();
    // if id exist
    if(lId != "") {
        lData = getWord(lId);
    }
    // if id no exist
    else {
        m_dom->getRoot("rdv").getNode("menus");
        m_dom->getNodeItem("menu", _menu).getNodeOrEmpty("name");
        lData = m_dom->getNodeValueOrEmpty();
    }
    return lData;
}
//===============================================
bool GQtMainWindow::getMenuSep(int _menu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNodeOrEmpty("menusep");
    bool lData = (m_dom->getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
QString GQtMainWindow::getBoxMenuName(int _menu, int _submenu, int _box) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNode("menu");
    m_dom->getNode("submenus").getNodeItem("submenu", _box);
    m_dom->getNodeOrEmpty("name");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getBoxMenuKey(int _menu, int _submenu, int _box) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNode("menu");
    m_dom->getNode("submenus").getNodeItem("submenu", _box);
    m_dom->getNodeOrEmpty("key");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
}
//===============================================
bool GQtMainWindow::getMenuToolBarOn(int _index) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _index).getNodeOrEmpty("toolbar");
    bool lData = (m_dom->getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuName(int _menu, int _submenu) const {
    QString lData;
    // get id
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("id");
    QString lId = m_dom->getNodeValueOrEmpty();
    // if id exist
    if(lId != "") {
        lData = getWord(lId);
    }
    // if id no exist
    else {
        m_dom->getRoot("rdv").getNode("menus");
        m_dom->getNodeItem("menu", _menu).getNode("submenus");
        m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("name");
        lData = m_dom->getNodeValueOrEmpty();
    }
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuBoxName(int _menu, int _submenu) const {
    QString lData;
    // get id
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("menu");
    m_dom->getNodeOrEmpty("id");
    QString lId = m_dom->getNodeValueOrEmpty();
    // if id exist
    if(lId != "") {
        lData = getWord(lId);
    }
    // if id no exist
    else {
        m_dom->getRoot("rdv").getNode("menus");
        m_dom->getNodeItem("menu", _menu).getNode("submenus");
        m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("menu");
        m_dom->getNodeOrEmpty("name");
        lData = m_dom->getNodeValueOrEmpty();
    }
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuBoxKey(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("menu");
    m_dom->getNodeOrEmpty("key");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuBoxRecentFileOn(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("menu");
    bool lData = m_dom->hasNode("recentfile");
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuBoxCtrlOn(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("menu");
    m_dom->getNodeOrEmpty("ctrl");
    bool lData = (m_dom->getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
int GQtMainWindow::getSubMenuBoxRecentFileMaxValue(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("menu");
    m_dom->getNodeOrEmpty("recentfile").getNodeOrEmpty("max");
    int lData = m_dom->getNodeValueOrEmpty().toInt();
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuBoxRecentFileMaxCtrlOn(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("menu");
    m_dom->getNodeOrEmpty("recentfile").getNodeOrEmpty("ctrl");
    bool lData = (m_dom->getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuBoxRecentFileMaxKey(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("menu");
    m_dom->getNodeOrEmpty("recentfile").getNodeOrEmpty("key");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuIcon(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("icon");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuCheckBox(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("checkbox");
    bool lData = (m_dom->getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuStatusTip(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("statustip");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuKey(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("key");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getSubMenuShortcut(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("shortcut");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuToolBarOn(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("toolbar");
    bool lData = (m_dom->getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuToolBarSep(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("toolbarsep");
    bool lData = (m_dom->getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuSeparatorOn(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("separator");
    bool lData = (m_dom->getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
bool GQtMainWindow::getSubMenuCtrlOn(int _menu, int _submenu) const {
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", _menu).getNode("submenus");
    m_dom->getNodeItem("submenu", _submenu).getNodeOrEmpty("ctrl");
    bool lData = (m_dom->getNodeValueOrEmpty() == "1");
    return lData;
}
//===============================================
QString GQtMainWindow::getTitle() const {
    m_dom->getRoot("rdv").getNode("settings");
    m_dom->getNode("appname");
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getVersion() const {
    m_dom->getRoot("rdv").getNode("settings");
    m_dom->getNode("version");
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GQtMainWindow::getAbout() const {
    QString lData;
    // get id
    m_dom->getRoot("rdv").getNode("settings");
    m_dom->getNode("about").getNodeOrEmpty("id");
    QString lId = m_dom->getNodeValueOrEmpty();
    // if id exist
    if(lId != "") {
        lData = getWordCData(lId);
    }
    // if id no exist
    else {
        m_dom->getRoot("rdv").getNode("settings");
        m_dom->getNode("about").getNode("text");
        lData = m_dom->getCData();
    }
    return lData;
}
//===============================================
QString GQtMainWindow::getLogo() const {
    m_dom->getRoot("rdv").getNode("settings");
    m_dom->getNode("logo");
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GQtMainWindow::getWidth() const {
    m_dom->getRoot("rdv").getNode("settings");
    m_dom->getNode("width");
    int lData = m_dom->getNodeValue().toInt();
    return lData;
}
//===============================================
int GQtMainWindow::getHeight() const {
    m_dom->getRoot("rdv").getNode("settings");
    m_dom->getNode("height");
    int lData = m_dom->getNodeValue().toInt();
    return lData;
}
//===============================================
QString GQtMainWindow::getWindowFlag() const {
    m_dom->getRoot("rdv").getNode("settings");
    m_dom->getNodeOrEmpty("windowflag");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getUntitledName() const {
    m_dom->getRoot("rdv").getNode("untitled");
    m_dom->getNodeOrEmpty("name");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
}
//===============================================
QString GQtMainWindow::getUntitledExtension() const {
    m_dom->getRoot("rdv").getNode("untitled");
    m_dom->getNodeOrEmpty("extension");
    QString lData = m_dom->getNodeValueOrEmpty();
    return lData;
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
    QString lData;
    // count word
    m_domWord->getRoot("rdv").getNode("words");
    int lCountWord = m_domWord->countNode("word");
    // loop word
    int i = 0;
    for(; i < lCountWord; i++) {
        // get word id
        m_domWord->getRoot("rdv").getNode("words");
        m_domWord->getNodeItem("word", i).getNodeOrEmpty("id");
        QString lId = m_domWord->getNodeValueOrEmpty();
        if(lId == _id) {
            // get word by lang
            m_domWord->getRoot("rdv").getNode("words");
            m_domWord->getNodeItem("word", i).getNodeOrEmpty(_lang);
            lData = m_domWord->getNodeValueOrEmpty();
            if(lData == "") {
                GQTLOG->addError(QString("Erreur la methode (getWord) a echoue\n"
                        "sur l'id (%1) et la langue (%2) (1).").arg(_id).arg(_lang));
            }
            break;
        }
    }
    if(i == lCountWord) {
        GQTLOG->addError(QString("Erreur la methode (getWord) a echoue\n"
                "sur l'id (%1) et la langue (%2) (2).").arg(_id).arg(_lang));
    }
    return lData;
}
//===============================================
QString GQtMainWindow::getWordCData(const QString& _id, const QString& _lang) const {
    QString lData;
    // count word
    m_domWord->getRoot("rdv").getNode("words");
    int lCountWord = m_domWord->countNode("word");
    // loop word
    int i = 0;
    for(; i < lCountWord; i++) {
        // get word id
        m_domWord->getRoot("rdv").getNode("words");
        m_domWord->getNodeItem("word", i).getNodeOrEmpty("id");
        QString lId = m_domWord->getNodeValueOrEmpty();
        if(lId == _id) {
            // get word by lang
            m_domWord->getRoot("rdv").getNode("words");
            m_domWord->getNodeItem("word", i).getNodeOrEmpty(_lang);
            lData = m_domWord->getCData();
            if(lData == "") {
                GQTLOG->addError(QString("Erreur la methode (getWordCData) a echoue\n"
                        "sur l'id (%1) et la langue (%2) (1).").arg(_id).arg(_lang));
            }
            break;
        }
    }
    if(i == lCountWord) {
        GQTLOG->addError(QString("Erreur la methode (getWord) a echoue\n"
                "sur l'id (%1) et la langue (%2) (2).").arg(_id).arg(_lang));
    }
    return lData;
}
//===============================================
QString GQtMainWindow::getWordLang() const {
    m_domData->getRoot("rdv").getNode("lang");
    QString lData = m_domData->getNodeValueOrEmpty();
    return lData;
}
//===============================================
void GQtMainWindow::setLanguage(const QString& _lang) {
    m_domData->getRoot("rdv").getNode("lang");
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
    m_dom->getRoot("rdv").getNode("menus");
    m_dom->getNodeItem("menu", i).getNode("submenus");
    m_dom->getNodeItem("submenu", j).getNode("menu");
    m_dom->getNodeOrEmpty("index");
    m_dom->setNodeValue(QString("%1").arg(lIndex));
    // save dom
    m_dom->saveXmlFile();
}
//===============================================
void GQtMainWindow::writeGeometry(const QByteArray& _geometry) {
    m_domData->getRoot("rdv").getNode("geometry");
    m_domData->setNodeValue(_geometry.toBase64());
    m_domData->saveXmlFile();
}
//===============================================
QByteArray GQtMainWindow::getGeometry() const {
    m_domData->getRoot("rdv").getNode("geometry");
    QString lData = m_domData->getCData();
    QByteArray lData64;
    lData64 += lData;
    QByteArray lDataBA = QByteArray::fromBase64(lData64);
    return lDataBA;
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
