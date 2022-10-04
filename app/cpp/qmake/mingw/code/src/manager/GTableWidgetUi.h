//===============================================
#ifndef _GTableWidgetUi_
#define _GTableWidgetUi_
//===============================================
#include <QDialog>
//===============================================
namespace Ui {
    class GTableWidgetUi;
}
//===============================================
class GTableWidgetUi : public QDialog {
    Q_OBJECT

public:
    GTableWidgetUi(QWidget* parent = 0);
    ~GTableWidgetUi();

public slots:
void on_btnSelect_clicked();
void on_btnNext_clicked();

private:
    Ui::GTableWidgetUi *ui;
};
//==============================================
#endif
//==============================================
