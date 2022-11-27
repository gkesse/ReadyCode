//===============================================
#ifndef _GConfigUi_
#define _GConfigUi_
//===============================================
#include "GInclude.h"
//===============================================
class GModule2;
//===============================================
namespace Ui {
    class GConfigUi;
}
//===============================================
class GConfigUi : public QFrame {
    Q_OBJECT

public:
    GConfigUi(QWidget* parent = 0);
    ~GConfigUi();

    void readData();
    void writeData();

public slots:
    // module
    void on_btnSaveModule_clicked();
    void on_btnSearchModule_clicked();
    void on_btnNewModule_clicked();

private:
    Ui::GConfigUi *ui;
    std::shared_ptr<GModule2> m_module;
};
//==============================================
#endif
//==============================================
