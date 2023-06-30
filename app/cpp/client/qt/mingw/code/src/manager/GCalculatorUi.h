//===============================================
#ifndef _GCalculatorUi_
#define _GCalculatorUi_
//===============================================
#include "GWidget.h"
#include "GCalculator.h"
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
    void addCalculator(const GCalculator& _calc, int i, int _size);
    void showCalculator();

public slots:
    void on_edtExpression_returnPressed();

private:
    Ui::GCalculatorUi* ui;
    GCalculator m_calcMap;
    std::shared_ptr<QWidget> m_widResult;
    QVBoxLayout* m_layResult;
};
//===============================================
#endif
//===============================================
