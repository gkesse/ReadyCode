//===============================================
#ifndef _GCalculatorUi_
#define _GCalculatorUi_
//===============================================
#include "GWidget.h"
//===============================================
namespace Ui {
class GCalculatorUi;
}
//===============================================
class GCalculatorUi : public GWidget {
    Q_OBJECT

public:
    GCalculatorUi(QWidget* _parent = 0);
    ~GCalculatorUi();

public slots:
    void on_edtExpression_returnPressed();

private:
    Ui::GCalculatorUi* ui;
};
//===============================================
#endif
//===============================================
