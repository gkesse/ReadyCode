//===============================================
#ifndef _GQtMainWindow_
#define _GQtMainWindow_
//===============================================
#include "GInclude.h"
//===============================================
class GQtXml;
//===============================================
class GQtMainWindow : public QMainWindow {
    Q_OBJECT

public:
    GQtMainWindow(QWidget* _parent = 0);
    ~GQtMainWindow();
    void createActions();
    void setWindowFlag(QWidget* _parent);
    void prependToRecentFiles(const QString& _filename);
    void setRecentFilesVisible(bool _visible);
    QStringList readRecentFiles();
    int countRecentFiles() const;
    QString getRecentFile(int _name) const;
    void writeRecentFiles(QStringList _recentFiles);
    void clearRecentFiles();
    void appendRecentFile(QString _recentFile);
    int countMenus() const;
    int countSubMenus(int _menu) const;
    int countBoxMenus(int _menu, int _submenu) const;
    QString getMenuName(int _menu) const;
    QString getBoxMenuName(int _menu, int _submenu, int _box) const;
    bool getMenuToolBarOn(int _index) const;
    QString getSubMenuName(int _menu, int _submenu) const;
    QString getSubMenuBox(int _menu, int _submenu) const;
    QString getSubMenuIcon(int _menu, int _submenu) const;
    QString getSubMenuStatusTip(int _menu, int _submenu) const;
    QString getSubMenuKey(int _menu, int _submenu) const;
    QString getSubMenuShortcut(int _menu, int _submenu) const;
    bool getSubMenuToolBarOn(int _menu, int _submenu) const;
    bool getSubMenuSeparatorOn(int _menu, int _submenu) const;
    QString getTitle() const;
    QString getLogo() const;
    int getWidth() const;
    int getHeight() const;
    QString getWindowFlag() const;
    QString getUntitledName() const;
    QString getUntitledExtension() const;

public slots:
    virtual void onMenuAction();

protected:
QSharedPointer<GQtXml> m_dom;
QSharedPointer<GQtXml> m_domData;
};
//==============================================
#endif
//==============================================
