//===============================================
#ifndef GLOGUI_H
#define GLOGUI_H
//===============================================
#include "GDialog.h"
//===============================================
#define GLOGI   GLogUi::Instance()
//===============================================
namespace Ui {
class GLogUi;
}
//===============================================
class GLogUi : public GDialog {
    Q_OBJECT

public:
    GLogUi(QWidget* _parent = 0);
    ~GLogUi();
    static GLogUi* Instance();

private:
    static GLogUi* m_instance;
    Ui::GLogUi* ui;
};
//===============================================
#endif
//===============================================
