//===============================================
#ifndef _GTableWidgetUi_
#define _GTableWidgetUi_
//===============================================
#include "GInclude.h"
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

    void initTableWidget();
    void setSize(int _rows, int _cols);
    void setHeader(int _col, const GString& _data);
    void setData(int _row, int _col, const GString& _data);

public slots:
    void on_btnSelect_clicked();
    void on_btnNext_clicked();

private:
    Ui::GTableWidgetUi *ui;
};
//==============================================
#endif
//==============================================
