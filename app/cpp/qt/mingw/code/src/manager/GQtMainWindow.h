//===============================================
#ifndef _GQtMainWindow_
#define _GQtMainWindow_
//===============================================
#include "GInclude.h"
//===============================================
class GQtXml;
class GObject;
//===============================================
class GQtMainWindow : public QMainWindow {
    Q_OBJECT

public:
    GQtMainWindow(QWidget* _parent = 0);
    ~GQtMainWindow();
    //
    virtual void createActions();
    virtual void createStatusBar();
    virtual void setWindowFlag(QWidget* _parent);
    virtual void prependToRecentFiles(const QString& _filename);
    virtual void setRecentFilesVisible(bool _visible, const QString& _recentFileKey = "file/recent", const QString& _separatorKey = "file/recent/separator");
    virtual QStringList readRecentFiles();
    virtual void updateRecentFiles(const QString& _recentFileMaxKey = "file/recent/max", const QString& _recentFileKey = "file/recent");
    virtual QString strippedName(const QString& _fullname);
    //
    virtual int countRecentFiles() const;
    virtual bool hasRecentFiles() const;
    virtual QString getRecentFile(int _name) const;
    virtual void writeRecentFiles(QStringList _recentFiles);
    virtual void clearRecentFiles();
    virtual void appendRecentFile(QString _recentFile);
    //
    virtual void createDoms();
    virtual QString getTitle() const;
    virtual QString getVersion() const;
    virtual QString getAbout() const;
    virtual QString getAboutId() const;
    virtual QString getAboutText() const;
    virtual QString getLogo() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual QString getWindowFlag() const;
    virtual QString getUntitledName() const;
    virtual QString getUntitledExtension() const;
    virtual int countMenus() const;
    virtual int countSubMenus(int _menu) const;
    virtual int countBoxMenus(int _menu, int _submenu) const;
    virtual bool getRadioButton(int _menu, int _submenu) const;
    virtual QString getMenuKey(int _menu, int _submenu) const;
    virtual int getMenuIndex(int _menu, int _submenu) const;
    virtual bool getMenuIndexCtrl(int _menu, int _submenu) const;
    virtual QString getMenuName(int _menu) const;
    virtual QString getMenuNameId(int _menu) const;
    virtual QString getMenuNameText(int _menu) const;
    virtual bool getMenuSep(int _menu) const;
    virtual QString getBoxMenuName(int _menu, int _submenu, int _box) const;
    virtual QString getBoxMenuKey(int _menu, int _submenu, int _box) const;
    virtual bool getMenuToolBarOn(int _menu) const;
    virtual QString getSubMenuName(int _menu, int _submenu) const;
    virtual QString getSubMenuNameId(int _menu, int _submenu) const;
    virtual QString getSubMenuNameText(int _menu, int _submenu) const;
    virtual QString getSubMenuBoxName(int _menu, int _submenu) const;
    virtual QString getSubMenuBoxNameId(int _menu, int _submenu) const;
    virtual QString getSubMenuBoxNameText(int _menu, int _submenu) const;
    virtual QString getSubMenuBoxKey(int _menu, int _submenu) const;
    virtual bool getSubMenuBoxRecentFileOn(int _menu, int _submenu) const;
    virtual bool getSubMenuBoxCtrlOn(int _menu, int _submenu) const;
    virtual int getSubMenuBoxRecentFileMaxValue(int _menu, int _submenu) const;
    virtual bool getSubMenuBoxRecentFileMaxCtrlOn(int _menu, int _submenu) const;
    virtual QString getSubMenuBoxRecentFileMaxKey(int _menu, int _submenu) const;
    virtual QString getSubMenuIcon(int _menu, int _submenu) const;
    virtual bool getSubMenuCheckBox(int _menu, int _submenu) const;
    virtual QString getSubMenuStatusTip(int _menu, int _submenu) const;
    virtual QString getSubMenuKey(int _menu, int _submenu) const;
    virtual QString getSubMenuShortcut(int _menu, int _submenu) const;
    virtual bool getSubMenuToolBarOn(int _menu, int _submenu) const;
    virtual bool getSubMenuToolBarSep(int _menu, int _submenu) const;
    virtual bool getSubMenuSeparatorOn(int _menu, int _submenu) const;
    virtual bool getSubMenuCtrlOn(int _menu, int _submenu) const;
    virtual QString getWord(const QString& _id) const;
    virtual QString getWordCData(const QString& _id) const;
    virtual QString getWord(const QString& _id, const QString& _lang) const;
    virtual QString getWordCData(const QString& _id, const QString& _lang) const;
    virtual QString getWordLang() const;
    virtual void setLanguage(const QString& _lang);
    virtual void setLanguageIndex(const QString& _key, const QString& _languageKey = "help/language");
    virtual void setLanguageIndex(int _menu, int _submenu, int _index);
    virtual void writeGeometry(const QByteArray& _geometry);
    virtual QByteArray getGeometry() const;
    virtual bool getDebug() const;
    virtual void showDebug(const std::string& _debug);
    virtual void showDebug(const QString& _debug);
    //
    virtual QAction* getKeyAction(const QString& _key) const;
    virtual int getKeyInt(const QString& _key) const;
    virtual QString getKeyIndex(const QString& _key, int _index) const;
    virtual QObject* getObject(const QString& _key);

public slots:
    virtual void onMenuAction();
    virtual void onMenuAction(bool _checked);
    virtual void onMenuBox();
    virtual void onBoxRecentFile();

protected:
    QSharedPointer<GQtXml> m_dom;
    QSharedPointer<GQtXml> m_domData;
    QSharedPointer<GQtXml> m_domWord;
    //
    QMap<QMenu*, QString> m_menuKey;
    QMap<QString, QAction*> m_keyAction;
    QMap<QString, int> m_keyInt;
    //
    QMap<QObject*, QString> m_objectMap;
    QMap<QString, QObject*> m_keyObject;
    //
    QSharedPointer<GObject> m_requestDom;
};
//==============================================
#endif
//==============================================
