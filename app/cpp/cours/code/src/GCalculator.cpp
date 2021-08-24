//===============================================
#include "GCalculator.h"
//===============================================
GCalculator::GCalculator(QWidget* parent) : GQtUi(parent) {
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    for (int i = 0; i < NumDigitButtons; ++i) {
        GCalculatorButton* digitButton = createButton(QString::number(i), SLOT(onEvent()));
        widgetMap[digitButton] = "digit";
        digitButtons[i] = digitButton;
    }

    GCalculatorButton* pointButton = createButton(tr("."), SLOT(onEvent()));
    widgetMap[pointButton] = "point";
    GCalculatorButton* changeSignButton = createButton(tr("\302\261"), SLOT(onEvent()));
    widgetMap[changeSignButton] = "change_sign";

    GCalculatorButton* backspaceButton = createButton(tr("Backspace"), SLOT(onEvent()));
    widgetMap[backspaceButton] = "backspace";
    GCalculatorButton* clearButton = createButton(tr("Clear"), SLOT(onEvent()));
    widgetMap[clearButton] = "clear";
    GCalculatorButton* clearAllButton = createButton(tr("Clear All"), SLOT(onEvent()));
    widgetMap[clearAllButton] = "clear_all";

    GCalculatorButton* clearMemoryButton = createButton(tr("MC"), SLOT(onEvent()));
    widgetMap[clearMemoryButton] = "clear_memory";
    GCalculatorButton* readMemoryButton = createButton(tr("MR"), SLOT(onEvent()));
    widgetMap[readMemoryButton] = "read_memory";
    GCalculatorButton* setMemoryButton = createButton(tr("MS"), SLOT(onEvent()));
    widgetMap[setMemoryButton] = "set_memory";
    GCalculatorButton* addToMemoryButton = createButton(tr("M+"), SLOT(onEvent()));
    widgetMap[addToMemoryButton] = "add_to_memory";

    GCalculatorButton* divisionButton = createButton(tr("\303\267"), SLOT(onEvent()));
    widgetMap[divisionButton] = "division";
    GCalculatorButton* timesButton = createButton(tr("\303\227"), SLOT(onEvent()));
    widgetMap[timesButton] = "times";
    GCalculatorButton* minusButton = createButton(tr("-"), SLOT(onEvent()));
    widgetMap[minusButton] = "minus";
    GCalculatorButton* plusButton = createButton(tr("+"), SLOT(onEvent()));
    widgetMap[plusButton] = "plus";

    GCalculatorButton* squareRootButton = createButton(tr("Sqrt"), SLOT(onEvent()));
    widgetMap[squareRootButton] = "square_root";
    GCalculatorButton* powerButton = createButton(tr("x\302\262"), SLOT(onEvent()));
    widgetMap[powerButton] = "power";
    GCalculatorButton* reciprocalButton = createButton(tr("1/x"), SLOT(onEvent()));
    widgetMap[reciprocalButton] = "reciprocal";
    GCalculatorButton* equalButton = createButton(tr("="), SLOT(onEvent()));
    widgetMap[equalButton] = "equal";

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 4, 1, 2);

    mainLayout->addWidget(clearMemoryButton, 2, 0);
    mainLayout->addWidget(readMemoryButton, 3, 0);
    mainLayout->addWidget(setMemoryButton, 4, 0);
    mainLayout->addWidget(addToMemoryButton, 5, 0);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);

    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5);

    setLayout(mainLayout);

    waitingForOperand = true;
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
}
//===============================================
GCalculator::~GCalculator() {

}
//===============================================
GCalculatorButton* GCalculator::createButton(const QString &text, const char *member) {
    GCalculatorButton* button = new GCalculatorButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
//===============================================
bool GCalculator::calculate(double rightOperand, const QString &pendingOperator) {
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0) {
            return false;
        }
        factorSoFar /= rightOperand;
    }
    return true;
}
//===============================================
void GCalculator::abortOperation() {
    onEvent("clear_all");
    display->setText(tr("####"));
}
//===============================================
void GCalculator::onEvent() {
    GCalculatorButton* clickedButton = qobject_cast<GCalculatorButton*>(sender());
    QString key = widgetMap[clickedButton];
    onEvent(key);
}
//===============================================
void GCalculator::onEvent(const QString& key) {
    // digit
    if(key == "digit") {
        GCalculatorButton* clickedButton = qobject_cast<GCalculatorButton*>(sender());
        int digitValue = clickedButton->text().toInt();
        if (display->text() == "0" && digitValue == 0) {
            return;
        }

        if (waitingForOperand) {
            display->clear();
            waitingForOperand = false;
        }

        display->setText(display->text() + QString::number(digitValue));
    }
    // point
    else if(key == "point") {
        if (waitingForOperand) {
            display->setText("0");
        }
        if (!display->text().contains('.')) {
            display->setText(display->text() + tr("."));
        }
        waitingForOperand = false;
    }
    // change_sign
    else if(key == "change_sign") {
        QString text = display->text();
        double value = text.toDouble();

        if (value > 0.0) {
            text.prepend(tr("-"));
        } else if (value < 0.0) {
            text.remove(0, 1);
        }

        display->setText(text);
    }
    // backspace
    else if(key == "backspace") {
        if (waitingForOperand) {
            return;
        }

        QString text = display->text();
        text.chop(1);

        if (text.isEmpty()) {
            text = "0";
            waitingForOperand = true;
        }

        display->setText(text);
    }
    // clear
    else if(key == "clear") {
        if (waitingForOperand) {
            return;
        }

        display->setText("0");
        waitingForOperand = true;
    }
    // clear_all
    else if(key == "clear_all") {
        sumSoFar = 0.0;
        factorSoFar = 0.0;
        pendingAdditiveOperator.clear();
        pendingMultiplicativeOperator.clear();
        display->setText("0");
        waitingForOperand = true;
    }
    // clear_memory
    else if(key == "clear_memory") {
        sumInMemory = 0.0;
    }
    // read_memory
    else if(key == "read_memory") {
        display->setText(QString::number(sumInMemory));
        waitingForOperand = true;
    }
    // set_memory
    else if(key == "set_memory") {
        onEvent("equal");
        sumInMemory = display->text().toDouble();
    }
    // add_to_memory
    else if(key == "add_to_memory") {
        onEvent("equal");
        sumInMemory += display->text().toDouble();
    }
    // division
    else if(key == "division") {
        onEvent("division_times");
    }
    // times
    else if(key == "times") {
        onEvent("division_times");
    }
    // division_times
    else if(key == "division_times") {
        GCalculatorButton* clickedButton = qobject_cast<GCalculatorButton*>(sender());
        if (!clickedButton) {
            return;
        }
        QString clickedOperator = clickedButton->text();
        double operand = display->text().toDouble();

        if (!pendingMultiplicativeOperator.isEmpty()) {
            if (!calculate(operand, pendingMultiplicativeOperator)) {
                abortOperation();
                return;
            }
            display->setText(QString::number(factorSoFar));
        }
        else {
            factorSoFar = operand;
        }

        pendingMultiplicativeOperator = clickedOperator;
        waitingForOperand = true;
    }
    // minus
    else if(key == "minus") {
        onEvent("minus_plus");
    }
    // plus
    else if(key == "plus") {
        onEvent("minus_plus");
    }
    // minus_plus
    else if(key == "minus_plus") {
        GCalculatorButton *clickedButton = qobject_cast<GCalculatorButton*>(sender());
        if (!clickedButton) {
            return;
        }

        QString clickedOperator = clickedButton->text();
        double operand = display->text().toDouble();

        if (!pendingMultiplicativeOperator.isEmpty()) {
            if (!calculate(operand, pendingMultiplicativeOperator)) {
                abortOperation();
                return;
            }
            display->setText(QString::number(factorSoFar));
            operand = factorSoFar;
            factorSoFar = 0.0;
            pendingMultiplicativeOperator.clear();
        }

        if (!pendingAdditiveOperator.isEmpty()) {
            if (!calculate(operand, pendingAdditiveOperator)) {
                abortOperation();
                return;
            }
            display->setText(QString::number(sumSoFar));
        }
        else {
            sumSoFar = operand;
        }

        pendingAdditiveOperator = clickedOperator;
        waitingForOperand = true;
    }
    // square_root
    else if(key == "square_root") {
        onEvent("square_root_power_reciprocal");
    }
    // power
    else if(key == "power") {
        onEvent("square_root_power_reciprocal");
    }
    // reciprocal
    else if(key == "reciprocal") {
        onEvent("square_root_power_reciprocal");
    }
    // square_root_power_reciprocal
    else if(key == "square_root_power_reciprocal") {
        GCalculatorButton *clickedButton = qobject_cast<GCalculatorButton*>(sender());
        QString clickedOperator = clickedButton->text();
        double operand = display->text().toDouble();
        double result = 0.0;

        if (clickedOperator == tr("Sqrt")) {
            if (operand < 0.0) {
                abortOperation();
                return;
            }
            result = std::sqrt(operand);
        }
        else if (clickedOperator == tr("x\302\262")) {
            result = std::pow(operand, 2.0);
        }
        else if (clickedOperator == tr("1/x")) {
            if (operand == 0.0) {
                abortOperation();
                return;
            }
            result = 1.0 / operand;
        }
        display->setText(QString::number(result));
        waitingForOperand = true;
    }
    // equal
    else if(key == "equal") {
        double operand = display->text().toDouble();

        if (!pendingMultiplicativeOperator.isEmpty()) {
            if (!calculate(operand, pendingMultiplicativeOperator)) {
                abortOperation();
                return;
            }
            operand = factorSoFar;
            factorSoFar = 0.0;
            pendingMultiplicativeOperator.clear();
        }
        if (!pendingAdditiveOperator.isEmpty()) {
            if (!calculate(operand, pendingAdditiveOperator)) {
                abortOperation();
                return;
            }
            pendingAdditiveOperator.clear();
        } else {
            sumSoFar = operand;
        }

        display->setText(QString::number(sumSoFar));
        sumSoFar = 0.0;
        waitingForOperand = true;
    }
}
//===============================================
