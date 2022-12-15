//===============================================
#ifndef _GWindowUi_
#define _GWindowUi_
//===============================================
#include "GInclude.h"
//===============================================
class GConnection;
class GFile;
class GModule;
//===============================================
namespace Ui {
    class GWindowUi;
}
//===============================================
class GWindowUi : public QMainWindow {
    Q_OBJECT

public:
    GWindowUi(QWidget* parent = 0);
    ~GWindowUi();

public slots:
    // managers
    void on_actionConfig_triggered();
    void on_actionQuery_triggered();

private:
    Ui::GWindowUi *ui;
};
//==============================================
#endif
//==============================================
