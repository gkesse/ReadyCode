//===============================================
#ifndef _GModuleUi_
#define _GModuleUi_
//===============================================
#include "GInclude.h"
//===============================================
class GModules;
class GModulesData;
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
    void on_btnSaveData_clicked();
    void on_btnSearchData_clicked();
    void on_btnNewData_clicked();

private:
    Ui::GModuleUi *ui;
    GModules* m_modules;
    GModulesData* m_modulesData;
    int m_tabDataIndex;
    bool m_isVisibleTabData;
};
//==============================================
#endif
//==============================================
