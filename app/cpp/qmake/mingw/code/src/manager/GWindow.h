//===============================================
#ifndef _GWindow_
#define _GWindow_
//===============================================
#include <QMainWindow>
//===============================================
namespace Ui {
    class GWindow;
}
//===============================================
class GConnection;
//===============================================
class GWindow : public QMainWindow {
    Q_OBJECT

public:
    GWindow(QWidget* parent = 0);
    ~GWindow();

public slots:
    // connection
    void on_actionStartConnection_triggered();
    void on_actionStartDisconnection_triggered();
    // account
    void on_actionCreateAccount_triggered();
    void on_actionSearchAccount_triggered();
    void on_actionEnableAccount_triggered();
    void on_actionDisableAccount_triggered();
    void on_actionUpdateAccount_triggered();
    void on_actionDeleteAccount_triggered();
    // group
    void on_actionCreateGroup_triggered();
    void on_actionSearchGroup_triggered();
    void on_actionUpdateGroup_triggered();
    void on_actionDeleteGroup_triggered();
    // file
    void on_actionSaveFile_triggered();
    void on_actionSearchFile_triggered();
    void on_actionDownloadFile_triggered();
    void on_actionDeleteFile_triggered();
    // options
    void on_actionCreateOption_triggered();
    void on_actionSearchOption_triggered();
    void on_actionEnableOption_triggered();
    void on_actionDisableOption_triggered();
    void on_actionReadOption_triggered();
    void on_actionUpdateOption_triggered();
    void on_actionDeleteOption_triggered();

private:
    Ui::GWindow *ui;
};
//==============================================
#endif
//==============================================