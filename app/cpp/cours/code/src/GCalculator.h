//===============================================
#ifndef _GCalculator_
#define _GCalculator_
//===============================================
#include "GQtUi.h"
#include "GCalculatorButton.h"
//===============================================
class GCalculator : public GQtUi {
    Q_OBJECT
    
public:
    GCalculator(QWidget* parent = 0);
    virtual ~GCalculator();
    GCalculatorButton* createButton(const QString &text, const char *member);
    bool calculate(double rightOperand, const QString &pendingOperator);
    void abortOperation();

public slots:
    void onEvent();
    void onEvent(const QString& key);

private:
    enum { NumDigitButtons = 10 };

private:
    QLineEdit* display;
    GCalculatorButton *digitButtons[NumDigitButtons];
    QMap<GCalculatorButton*, QString> widgetMap;
    bool waitingForOperand;
    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    double sumInMemory;
};
//==============================================
#endif
//==============================================
