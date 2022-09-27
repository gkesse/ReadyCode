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
    void on_actionEnregistrerFichier_triggered();
    void on_actionTelechargerFichier_triggered();

private:
    Ui::GWindow *ui;
};
//==============================================
#endif
//==============================================
