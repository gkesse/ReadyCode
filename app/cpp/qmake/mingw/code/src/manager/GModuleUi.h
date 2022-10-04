//===============================================
#ifndef _GModuleUi_
#define _GModuleUi_
//===============================================
#include "GInclude.h"
//===============================================
class GModules;
//===============================================
namespace Ui {
    class GModuleUi;
}
//===============================================
class GModuleUi : public QFrame {
    Q_OBJECT

public:
    GModuleUi(QWidget* parent = 0);
    ~GModuleUi();

    void readData();
    void writeData();

public slots:
    void on_btnSave_clicked();
    void on_btnSearch_clicked();
    void on_btnNew_clicked();

private:
    Ui::GModuleUi *ui;
    GModules* m_modules;
};
//==============================================
#endif
//==============================================
