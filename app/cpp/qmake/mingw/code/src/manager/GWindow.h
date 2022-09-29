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
class GWindow : public QMainWindow {
    Q_OBJECT

public:
    GWindow(QWidget* parent = 0);
    ~GWindow();

public slots:
    // connection
    void on_actionStartConnection_triggered();
    // file
    void on_actionSaveFile_triggered();
    void on_actionDownloadFile_triggered();
    // options
    void on_actionCreateOption_triggered();
    void on_actionEnableOption_triggered();
    void on_actionDisableOption_triggered();
    void on_actionReadOption_triggered();
    void on_actionUpdateOption_triggered();
    void on_actionDeleteOption_triggered();
    void on_actionSearchOption_triggered();

private:
    Ui::GWindow *ui;
};
//==============================================
#endif
//==============================================
