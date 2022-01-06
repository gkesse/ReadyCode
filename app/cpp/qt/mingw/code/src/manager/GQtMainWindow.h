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
    virtual void createDoms();
    void createActions();
    virtual void createStatusBar();
    void setWindowFlag(QWidget* _parent);
    void prependToRecentFiles(const QString& _filename);
    virtual void setRecentFilesVisible(bool _visible, const QString& _recentFileKey = "file/recent", const QString& _separatorKey = "file/recent/separator");
    QStringList readRecentFiles();
    void updateRecentFiles(const QString& _recentFileMaxKey = "file/recent/max", const QString& _recentFileKey = "file/recent");
    QString strippedName(const QString& _fullname);
    int countRecentFiles() const;
    bool hasRecentFiles() const;
    QString getRecentFile(int _name) const;
    void writeRecentFiles(QStringList _recentFiles);
    void clearRecentFiles();
    void appendRecentFile(QString _recentFile);
    int countMenus() const;
    int countSubMenus(int _menu) const;
    int countBoxMenus(int _menu, int _submenu) const;
    QString getMenuName(int _menu) const;
    bool getMenuSep(int _menu) const;
    QString getBoxMenuName(int _menu, int _submenu, int _box) const;
    QString getBoxMenuKey(int _menu, int _submenu, int _box) const;
    bool getMenuToolBarOn(int _index) const;
    QString getSubMenuName(int _menu, int _submenu) const;
    QString getSubMenuBoxName(int _menu, int _submenu) const;
    QString getSubMenuBoxKey(int _menu, int _submenu) const;
    bool getSubMenuBoxRecentFileOn(int _menu, int _submenu) const;
    bool getSubMenuBoxCtrlOn(int _menu, int _submenu) const;
    int getSubMenuBoxRecentFileMaxValue(int _menu, int _submenu) const;
    bool getSubMenuBoxRecentFileMaxCtrlOn(int _menu, int _submenu) const;
    QString getSubMenuBoxRecentFileMaxKey(int _menu, int _submenu) const;
    QString getSubMenuIcon(int _menu, int _submenu) const;
    bool getSubMenuCheckBox(int _menu, int _submenu) const;
    QString getSubMenuStatusTip(int _menu, int _submenu) const;
    QString getSubMenuKey(int _menu, int _submenu) const;
    QString getSubMenuShortcut(int _menu, int _submenu) const;
    bool getSubMenuToolBarOn(int _menu, int _submenu) const;
    bool getSubMenuToolBarSep(int _menu, int _submenu) const;
    bool getSubMenuSeparatorOn(int _menu, int _submenu) const;
    bool getSubMenuCtrlOn(int _menu, int _submenu) const;
    QString getTitle() const;
    QString getVersion() const;
    QString getAbout() const;
    QString getLogo() const;
    int getWidth() const;
    int getHeight() const;
    QString getWindowFlag() const;
    QString getUntitledName() const;
    QString getUntitledExtension() const;
    QString getWord(const QString& _id) const;
    QString getWordCData(const QString& _id) const;
    QString getWord(const QString& _id, const QString& _lang) const;
    QString getWordCData(const QString& _id, const QString& _lang) const;
    QString getWordLang() const;
    void setLanguage(const QString& _lang);
    void setLanguageIndex(const QString& _key, const QString& _languageKey = "help/language");
    void writeGeometry(const QByteArray& _geometry);
    QByteArray getGeometry() const;
    QAction* getKeyAction(const QString& _key) const;
    int getKeyInt(const QString& _key) const;
    QString getKeyIndex(const QString& _key, int _index) const;

public slots:
    virtual void onMenuAction();
    virtual void onMenuAction(bool _checked);
    virtual void onMenuBox();
    virtual void onBoxRecentFile();

protected:
    QSharedPointer<GQtXml> m_dom;
    QSharedPointer<GQtXml> m_domData;
    QSharedPointer<GQtXml> m_domWord;
    QMap<QMenu*, QString> m_menuKey;
    QMap<QString, QAction*> m_keyAction;
    QMap<QString, int> m_keyInt;
};
//==============================================
#endif
//==============================================
