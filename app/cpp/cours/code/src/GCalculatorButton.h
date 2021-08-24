//===============================================
#ifndef _GCalculatorButton_
#define _GCalculatorButton_
//===============================================
#include "GInclude.h"
//===============================================
class GCalculatorButton : public QToolButton {
    Q_OBJECT
    
public:
    GCalculatorButton(const QString &text, QWidget* parent = 0);
    virtual ~GCalculatorButton();

protected:
    QSize sizeHint() const;
};
//==============================================
#endif
//==============================================
