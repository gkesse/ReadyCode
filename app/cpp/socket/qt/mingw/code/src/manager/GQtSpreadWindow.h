//===============================================
#ifndef _GQtSpreadWindow_
#define _GQtSpreadWindow_
//===============================================
#include "GQtMainWindow.h"
//===============================================
class GQtTableWidget;
class sGQt;
//===============================================
class GQtSpreadWindow : public GQtMainWindow {
    Q_OBJECT

public:
    GQtSpreadWindow(QWidget* _parent = 0);
    ~GQtSpreadWindow();
    void createActions();
    void createMenus();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString& _filename);
    void setCurrentFile(const QString& _filename);
    QString strippedName(const QString& _fullname);
    void updateRecentFileActions();
    bool okToContinue();
    void writeSettings();
    void readSettings();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void onNewFile();
    void onOpenFile();
    bool onSave();
    bool onSaveAs();
    void onOpenRecentFile();

private:
    static const int MaxRecentFiles = 5;
    //
    sGQt m_params;
    //
    GQtTableWidget* m_spreadsheet;
    QString m_currentFile;
    QStringList m_recentFiles;
    //
    QMenu* m_fileMenu;
    QAction* m_newAction;
    QAction* m_openAction;
    QAction* m_saveAction;
    QAction* m_saveAsAction;
    QAction* m_separatorAction;
    QAction* m_recentFileActions[MaxRecentFiles];
    QAction* m_exitAction;
    //
    QMenu* m_optionsMenu;
    QAction* m_showGridAction;
    QAction* m_autoRecalcAction;
};
//==============================================
#endif
//==============================================
