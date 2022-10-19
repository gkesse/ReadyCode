//===============================================
#ifndef _GTableWidgetFr_
#define _GTableWidgetFr_
//===============================================
#include "GInclude.h"
//===============================================
class GTableWidget;
//===============================================
namespace Ui {
    class GTableWidgetFr;
}
//===============================================
class GTableWidgetFr : public QFrame {
    Q_OBJECT

public:
    GTableWidgetFr(QWidget* parent = 0);
    ~GTableWidgetFr();
    GTableWidget* getTableWidget();

public slots:
    void on_btnNext_clicked();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::GTableWidgetFr *ui;
};
//==============================================
#endif
//==============================================
