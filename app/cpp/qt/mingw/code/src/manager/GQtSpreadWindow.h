//===============================================
#ifndef _GQtSpreadWindow_
#define _GQtSpreadWindow_
//===============================================
#include "GQtMainWindow.h"
//===============================================
class GQtSpreadSheet;
class GQtFindDialog;
//===============================================
class GQtSpreadWindow : public GQtMainWindow {
    Q_OBJECT

public:
    GQtSpreadWindow(QWidget* _parent = 0);
    ~GQtSpreadWindow();
    void createDoms();
    void createCentralWidget();
    void createStatusBar();
    void createContextMenu();
    bool getShowGrid() const;
    bool getAutoRecalculate() const;
    void setShowGrid(bool _showGrig);
    void setAutoRecalculate(bool _autoRecalculate);
    bool okToContinue();
    bool save();
    bool saveAs();
    bool saveFile(const QString& _fileName);
    bool loadFile(const QString& _filename);
    void setCurrentFile(const QString& _filename);
    QString strippedName(const QString& _fullname);
    void writeSettings();
    void readSettings();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void onMenuAction(bool _checked = false);
    void onMenuBox();
    void onBoxRecentFile();
    void updateStatusBar(int currentRow = 0, int currentColumn = 0, int previousRow = 0, int previousColumn = 0);
    void spreadsheetModified();

private:
    static const int MaxRecentFiles = 5;

private:
    GQtSpreadSheet* spreadsheet;
    QString curFile;
    GQtFindDialog* findDialog;
    QLabel* locationLabel;
    QLabel* formulaLabel;
};
//==============================================
#endif
//==============================================
